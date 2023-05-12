#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="on">ログ機能OnOff</param>
MultiLangTextController::MultiLangTextController(WriteData& writeData)
{
	this->writeData = writeData;
	this->pLogger = new UnicodeLogger(writeData.flagLogOutput);

	std::wstring msg = L"# Import File: " + writeData.importExcelFileFullPathWide;
	this->pLogger->log(msg);

	// クラス生成時に多言語使用状態にし、他の処理の前に多言語使用可能状況を準備する
	// 他の処理の際、enable:trueを確認すること
	this->isEnable = SetProjectMLEnable();

	if (!this->isEnable) {
		return;
	}

	bool result;
	result = this->GetPageNames(this->pageNames);
	if (!result) {
		this->isEnable = false;
		return;
	}

}

/// <summary>
/// デストラクタ
/// </summary>
MultiLangTextController::~MultiLangTextController()
{
	delete this->pLogger;
}

/// <summary>
/// テキストデータ群のSDKプロジェクトへのインポート
/// </summary>
/// <returns>成否</returns>
bool MultiLangTextController::ImportTextData()
{
	bool result = true;

	// UI側指定の言語名をページとして追加する
	result = AddPageNames();
	if (!result) {
		this->pLogger->log(L"[error]Failed to add language pages.");
		return false;
	}

	// 第一言語名を取得する
	this->firstPageName = this->GetFirstPageName();

	// 第一言語名がUI側の何列目かを取得する
	this->columnIndexOfFirstPageName = writeData.getColumnIndexOfPageName(this->firstPageName);

	result = ImportTextDataTable();

	return result;
}






/// <summary>
/// プロジェクトの多言語使用可否状態の取得
/// </summary>
/// <returns></returns>
bool MultiLangTextController::IsEnabled()
{
	return this->isEnable;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool MultiLangTextController::AddPageNames()
{
	// 言語ページ追加処理の有無確認
	if (writeData.flagAddIfLanguagePageNotFound)
	{
		// 言語ページ追加処理
		bool result = SetPageNames(writeData.languageNameList);
		if (!result) {
			this->pLogger->log(L"[error]Failed to add language pages.");
			return false;
		}
	}

	return true;
}


bool MultiLangTextController::ImportTextDataTable()
{
	int rowCount = (int)this->writeData.textDataTable.size();

	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		bool result = this->ImportTextDataRow(this->writeData.textCastNameList[rowIndex], this->writeData.textDataTable[rowIndex]);
		if (!result) {
			return false;
		}
	}

	return true;
}

bool MultiLangTextController::ImportTextDataRow(std::string& castname, std::vector<TextData>& textDataRow)
{
	bool result = false;

	// 指定の名前でキャストが既に存在するか確認する
	int castNumber = FindTextCastNumber(castname);
	if (0 <= castNumber) {
		// 指定の名前でキャストが既に存在する
	}
	else {
		// 指定の名前のキャストは存在しない
		// 不明なテキストキャストを新規に追加、するかどうか
		if (this->writeData.flagAddIfTextCastNotFound){
			// 追加する
			result = this->ImportTextDataAsNewCast(castname, textDataRow);
		}
		else {
			// 追加しない：何もしない
			// ログ：スキップ
			this->pLogger->log("CAST [" + castname + "]: Skipped");
			result = true;
		}
	}

	return result;
}

bool MultiLangTextController::ImportTextDataAsNewCast(std::string& castname, std::vector<TextData>& textDataRow)
{
	bool result = false;

	// キャスト番号の空きを取得
	int newCastNumber = this->GetNewTextCastNumber();
	int resultNumber;

	// キャストの文字データはUnicodeにするかどうか
	// UIのチェックで新規キャストはUni or テキストデータがUniでなければならない
	bool isUTF = this->writeData.flagCreateAsUnicodeTextCast || this->CheckTextDataRowMustBeUTF(textDataRow);
	if (isUTF) {
		resultNumber = MxPluginPort_Cast_CreateTextEx(newCastNumber, (char*)castname.c_str(), set_UTF);
	}
	else {
		resultNumber = MxPluginPort_Cast_CreateTextEx(newCastNumber, (char*)castname.c_str(), set_ANSI);
	}

	// テキストキャスト生成エラーを確認
	if (newCastNumber != resultNumber) {
		this->pLogger->log("[error]Failed to create new text cast[" + castname + "]" + (isUTF ? "[UTF]" : "[ANSI]"));
		return false;
	}

	bool isFirstPropInherit = (-1 != this->columnIndexOfFirstPageName);
	TextData inheritPropData;
	if (isFirstPropInherit) {
		inheritPropData = textDataRow[this->columnIndexOfFirstPageName];
	}

	int colCount = textDataRow.size();
	for (int colIndex = 0; colIndex < colCount; colIndex++) {
		result = SetTextDataCellToTextCast(newCastNumber, colIndex, textDataRow[colIndex], inheritPropData, isFirstPropInherit, isUTF);
		if (!result) {
			break;
		}
	}

	return result;
}



/// <summary>
/// 番号指定のテキストキャストにある言語のテキストデータを登録する
/// </summary>
/// <param name="castNumber">書き込み先テキストキャスト番号</param>
/// <param name="colIndex">UI側行番号</param>
/// <param name="textData">書き込みテキストデータ</param>
/// <param name="inheritPropData">継承用先頭言語テキストデータ（プロパティを使用）</param>
/// <param name="isFirstPropInherit">継承用先頭言語テキストデータ有効フラグ</param>
/// <param name="isUTF">文字列UTFフラグ</param>
/// <returns>成否</returns>
bool MultiLangTextController::SetTextDataCellToTextCast(int castNumber, int colIndex, TextData& textData, TextData& inheritPropData, bool isFirstPropInherit, bool isUTF)
{
	bool result = true;

	// 文字列が空白であれば無効データとみなしているので何もしない
	if (!textData.isValidData) {
		return true;
	}

	std::string langName = this->writeData.languageNameList[colIndex];
	
	int pageNumber = this->GetPageNumber(langName);
	if (pageNumber < 0) {
		// プロジェクトに言語ページが登録されていないので、追加せずスキップ
		return true;
	}

	bool createPageFlag = false;
	result = CreateLangPageToTextCast(castNumber, pageNumber, createPageFlag);
	if (!result) {
		// ログはCreateLangPageToTextCast関数の中にある
		return false;
	}

	result = SetTextProperty(castNumber, pageNumber, textData, inheritPropData, isFirstPropInherit, createPageFlag, isUTF);
	if (!result) {
		// ログはSetTextProperty関数の中にある
		return false;
	}

	return result;
}

/// <summary>
/// 番号指定のテキストキャストにプロジェクトの指定の言語ページを追加する（既存の場合は成功）
/// </summary>
/// <param name="castNumber">書き込み先テキストキャスト番号</param>
/// <param name="pageNumber">プロジェクト言語ページ番号</param>
/// <param name="createPageFlag">[out]新規ページ作成フラグ</param>
/// <returns>成否</returns>
bool MultiLangTextController::CreateLangPageToTextCast(int castNumber, int pageNumber, bool& createPageFlag)
{
	BOOL mxResult = FALSE;
	bool exist = false;

	// [out]
	createPageFlag = false;

	// 指定のテキストキャストに指定の言語ページがあるか確認する
	mxResult = MxPluginPort_Cast_Text_GetLanguageAssigned(castNumber, pageNumber, &exist);
	if (!mxResult) {
		this->pLogger->log("[error]Failed to check existance of language(" + ::to_string(pageNumber) + ") in the text cast number[" + ::to_string(castNumber) + "]");
		return false;
	}

	if (exist) {
		// 指定のテキストキャストには指定の言語ページがあるので成功・スキップ
		return true;
	}

	mxResult = MxPluginPort_Cast_Text_CreateLanguage(castNumber, pageNumber);
	if (!mxResult) {
		this->pLogger->log("[error]Failed to set language(" + ::to_string(pageNumber) + ") in the text cast number[" + ::to_string(castNumber) + "]");
		return false;
	}

	// [out]
	createPageFlag = true;
	return true;
}

/// <summary>
/// テキストキャスト新規作成用のキャスト番号を取得する
/// </summary>
/// <returns>キャスト番号</returns>
int MultiLangTextController::GetNewTextCastNumber()
{
	// キャスト番号の使用数を取得する（この関数は途中の虫食いを埋まっているとみなす）
	int number = MxPluginPort_Cast_GetCastCount(ct_Text);
	return number;
}

/// <summary>
/// プロジェクト内の言語リストを取得する
/// </summary>
/// <param name="list">空リスト（言語リスト登録用）</param>
/// <returns>成否</returns>
bool MultiLangTextController::GetPageNames(std::vector<std::string>& list)
{
	BOOL mxResult;
	int pageCount;

	// プロジェクト内の言語数を取得
	mxResult = MxPluginPort_Project_MultiLang_GetCount(&pageCount);
	if (!mxResult) {
		this->pLogger->log(L"[error]Failed to get count of language pages of project.");
		return false;
	}

	// プロジェクト内言語のそれぞれに対して。
	for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
	{
		char* pname = nullptr;
		
		// 言語名文字列(ANSI)を取得
		mxResult = MxPluginPort_Project_MultiLang_GetName(pageIndex, &pname);
		if (!mxResult) {
			this->pLogger->log(L"[error]Failed to get name of language page of number " + to_wstring(pageIndex));
			return false;
		}

		std::string pageName = std::string(pname);
		list.push_back(pageName);
	}

	return true;
}

/// <summary>
/// 言語名からプロジェクトの言語ページ番号を取得する
/// </summary>
/// <param name="pageName">言語名</param>
/// <returns>プロジェクトのページ番号(-1:存在せず）</returns>
int MultiLangTextController::GetPageNumber(std::string pageName)
{
	int pageNumber = -1;

	// SDK側言語リストからページ名を検索するイテレータを取得
	auto iter = std::find(this->pageNames.begin(), this->pageNames.end(), pageName);
	if (iter == this->pageNames.end()) {
		// 見つからない場合-1
		return pageNumber;
	}

	// 距離（インデクス）を取得
	pageNumber = std::distance(this->pageNames.begin(), iter);
	return pageNumber;
}

/// <summary>
/// デフォルト言語設定
/// </summary>
/// <param name="writeData">書き込み管理データ</param>
/// <returns>処理成否</returns>
bool MultiLangTextController::SetDefaultLanguage(WriteData& writeData)
{
	bool result = true;
	int mxResult;

	// デフォルト言語名
	writeData.defaultLanguageName;

	// デフォルト言語設定


	return result;
}

/// <summary>
/// テキストデータ行をUTFで扱わなければいけないか判定する
/// </summary>
/// <param name="textDataRow">UIテキストデータ行</param>
/// <returns>true:UTFであること, false:ANSIでも良い</returns>
bool MultiLangTextController::CheckTextDataRowMustBeUTF(std::vector<TextData>& textDataRow)
{
	int colCount = (int)textDataRow.size();

	// １つのテキストキャストの各言語のテキストでANSI変換できるかをチェックする
	for (int colIndex = 0; colIndex < colCount; colIndex++)
	{
		bool canConvToANSI = textDataRow[colIndex].canConvToANSI;
		// いずれかの言語でもANSI変換ができない場合
		if (!canConvToANSI) {
			// UTFでなければならない
			return true;
		}
	}
	// ANSIでもよい
	return false;
}

/// <summary>
/// プロジェクトの多言語使用状態をOnにする
/// </summary>
/// <returns>On化成否</returns>
bool MultiLangTextController::SetProjectMLEnable()
{
	BOOL mxResult;

	BOOL isEnabled = false;
	// 現プロジェクトが多言語使用可能か確認する
	mxResult = MxPluginPort_Project_MultiLang_GetEnabled(&isEnabled);

	if (!mxResult) {
		this->pLogger->log(L"[error]Failed to confirm availability of multi-language.");
		return false;
	}

	// 現在多言語未使用なら使用したいので、
	if (!isEnabled) {
		// 多言語を使用可能にする
		mxResult = MxPluginPort_Project_MultiLang_SetEnabled(true);
	}

	return mxResult;
}

/// <summary>
/// プロジェクトに使用したい言語ページを追加でセットする
/// 既存ページと重複する場合はスキップで成功とする
/// </summary>
/// <param name="list">追加使用したい言語ページ</param>
/// <returns>ページ設定の成否</returns>
bool MultiLangTextController::SetPageNames(std::vector<std::string>& list)
{
	std::vector<int> appendIndexList;

	// 追加したいページ名が既に存在するか確認し、ない場合、追加リストのインデックスでリストを作る
	for (size_t index = 0; index < list.size(); index++)
	{
		bool exists = std::find(this->pageNames.begin(), this->pageNames.end(), list[index]) != this->pageNames.end();
		// 存在しなかった場合、そのインデックスを保持する
		if (!exists)
		{
			appendIndexList.push_back(index);
		}
	}

	// 保持したインデックスの言語ページを追加する
	for (size_t index = 0; index < appendIndexList.size(); index++)
	{
		int pageIndex = appendIndexList[index];
		BOOL mxResult = MxPluginPort_Project_MultiLang_Add(list[pageIndex].c_str());
		if (!mxResult) {
			this->pLogger->log("[error]Failed to add language page: " + list[pageIndex]);
			return false;
		}

		std::string msg = "LANGUAGE [" + list[pageIndex] + "]: Added";
		this->pLogger->log(msg);
	}

	// 言語ページリストを更新する
	this->pageNames.clear();
	bool result = this->GetPageNames(this->pageNames);

	return true;
}

/// <summary>
/// ページ番号０の言語名を取得
/// </summary>
/// <returns>ページ番号０の言語名</returns>
string MultiLangTextController::GetFirstPageName() {
	string pageNameStr = "";
	bool mxResult = false;
	char* pageName = nullptr;
	mxResult = MxPluginPort_Project_MultiLang_GetName(0, &pageName);
	if (mxResult) {
		pageNameStr = string(pageName);
	}
	return pageNameStr;
}

/// <summary>
/// 
/// </summary>
/// <param name="castNumber">書き込み先テキストキャスト番号</param>
/// <param name="pageNumber">プロジェクト言語ページ番号</param>
/// <param name="textData">書き込みテキストデータ</param>
/// <param name="inheritPropData">継承用先頭言語テキストデータ</param>
/// <param name="isFirstPropInherit">継承用先頭言語テキストデータ有効フラグ</param>
/// <param name="createPageFlag">新規言語ページ作成発生フラグ</param>
/// <param name="isUTF">文字列UTFフラグ</param>
/// <returns>成否</returns>
bool MultiLangTextController::SetTextProperty(
	int castNumber, int pageNumber, TextData& textData, TextData& inheritPropData,
	bool isFirstPropInherit, bool createPageFlag, bool isUTF)
{
	bool mxResult = false;

	bool inherit;

	// 先頭言語ページの継承チェックを付けていない場合
	if (!this->writeData.flagInheritPropertiesOfTheFirstLangPage) {
		// 継承せず
		inherit = false;
	}
	else {
		// 新規の言語ページのみ継承チェック
		if (this->writeData.flagInheritOnlyNewLangPage) {
			// チェックつき
			// 新規言語ページの作成が発生していた時のみ継承する
			if (createPageFlag) {
				inherit = true;
			}
			else {
				inherit = false;
			}
		}
		else {
			// チェックなし->テキストキャストにすでに指定言語があっても継承する
			inherit = true;
		}
	}

	// 継承Onでも継承データが有効でない場合は継承しない
	if (!isFirstPropInherit) {
		inherit = false;
	}

	TextData usedPropData = inherit ? inheritPropData : textData;

	// フォント名をテキストキャストに反映チェック　対象：フォント名、フォントスタイル
	if (this->writeData.flagApplyFontNameToTextCast){
		// フォント名を設定
		mxResult = MxPluginPort_Cast_Text_SetFontName(castNumber, pageNumber, usedPropData.fontName.c_str());
		if (!mxResult) {
			this->pLogger->log(
				"[error]Failed to set font name[" + usedPropData.fontName + "] to Cast[" + ::to_string(castNumber) + "],Page[" + ::to_string(pageNumber) + "]"
			);
			return false;
		}

		// フォントスタイルを設定
		mxResult;
		if (!mxResult) {
			this->pLogger->log(
				"[error]Failed to set font style to Cast[" + ::to_string(castNumber) + "],Page[" + ::to_string(pageNumber) + "]"
			);
			return false;
		}
	}

	// フォントサイズをテキストキャストに反映チェック　対象：サイズ
	if (this->writeData.flagApplyFontSizeToTextCast) {
		mxResult = MxPluginPort_Cast_Text_SetFontSize(castNumber, pageNumber, (int)usedPropData.fontSize);
		if (!mxResult) {
			this->pLogger->log(
				"[error]Failed to set font size to Cast[" + ::to_string(castNumber) + "],Page[" + ::to_string(pageNumber) + "]"
			);
			return false;
		}
	}

	// 文字色をテキストキャストに反映チェック　対象：フォント色
	if (this->writeData.flagApplyTextColorToTextCast) {
		int colorValue = (textData.colorR & 0x000000ff)
			+ ((textData.colorG << 8) & 0x0000ff00)
			+ ((textData.colorB << 16) & 0x00ff0000);
		mxResult = MxPluginPort_Cast_Text_SetFontColor(castNumber, pageNumber, colorValue);
		if (!mxResult) {
			this->pLogger->log(
				"[error]Failed to set font color to Cast[" + ::to_string(castNumber) + "],Page[" + ::to_string(pageNumber) + "]"
			);
			return false;
		}
	}

	// 文字列をテキストキャストに反映チェック　文字列
	if (this->writeData.flagApplyStringToTextCast) {
		bool isUnicodeTextCast = true;
		if (isUTF) {
			mxResult = MxPluginPort_Cast_Text_SetTextDataWIDE(castNumber, pageNumber, textData.wtext.c_str());
			if (!mxResult) {
				this->pLogger->log(
					L"[error]Failed to set string to Cast[" + ::to_wstring(castNumber) + L"],Page[" + ::to_wstring(pageNumber) + L"]"
				);
				return false;
			}
		}
		else {
			mxResult = MxPluginPort_Cast_Text_SetTextDataANSI(castNumber, pageNumber, textData.text.c_str());
			if (!mxResult) {
				this->pLogger->log(
					"[error]Failed to set string to Cast[" + ::to_string(castNumber) + "],Page[" + ::to_string(pageNumber) + "]"
				);
				return false;
			}
		}
	}

	return true;
}

/// <summary>
/// キャスト名によるテキストキャスト番号検索
/// </summary>
/// <param name="castname">キャスト名</param>
/// <returns>キャスト番号（失敗：-1）</returns>
int MultiLangTextController::FindTextCastNumber(std::string& castname)
{
	int castNumber = MxPluginPort_Cast_FindCast(ct_Text, (char*)castname.c_str());
	return castNumber;
}


/// <summary>
/// テキストキャスト書き込みテスト関数
/// </summary>
void MultiLangTextController::TestWriteTextCast()
{
	int castCount;
	int castNumber = 10;
	int resultNumber;
	bool mxResult;

	castCount = MxPluginPort_Cast_GetCastCount(ct_Text);

	string castName = "Text10";
	string text10Eng = "Hello\nWorld";
	resultNumber = MxPluginPort_Cast_CreateTextEx(castNumber, (char*)castName.c_str(), set_ANSI);
	mxResult = MxPluginPort_Cast_Text_CreateLanguage(resultNumber, 0);
	mxResult = MxPluginPort_Cast_Text_SetTextDataANSI(resultNumber, 0, text10Eng.c_str());
	mxResult = MxPluginPort_Cast_Text_SetFontColor(resultNumber, 0, 0x0000ff);
	mxResult = MxPluginPort_Cast_Text_SetFontSize(resultNumber, 0, 20);

	castCount = MxPluginPort_Cast_GetCastCount(ct_Text);

	castNumber = 11;
	castName = "Text11";
	wstring text11Kor = L"아니\n오";
	resultNumber = MxPluginPort_Cast_CreateTextEx(castNumber, (char*)castName.c_str(), set_UTF);
	mxResult = MxPluginPort_Cast_Text_CreateLanguage(resultNumber, 2);
	mxResult = MxPluginPort_Cast_Text_SetTextDataWIDE(resultNumber, 2, text11Kor.c_str());
	mxResult = MxPluginPort_Cast_Text_SetFontColor(resultNumber, 2, 0x00ff00);
	mxResult = MxPluginPort_Cast_Text_SetFontSize(resultNumber, 2, 28);

	castCount = MxPluginPort_Cast_GetCastCount(ct_Text);
}
