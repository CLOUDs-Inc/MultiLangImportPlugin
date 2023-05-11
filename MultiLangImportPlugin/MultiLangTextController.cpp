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

bool MultiLangTextController::ImportTextData()
{
	bool result = true;

	// 第一言語名を取得する
	this->firstPageName = this->GetFirstPageName();

	// 第一言語名がUI側の何列目かを取得する
	this->columnIndexOfFirstPageName = writeData.getColumnIndexOfPageName(this->firstPageName);

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
		return false;
	}

	// プロジェクト内言語のそれぞれに対して。
	for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
	{
		char* pname = nullptr;
		
		// 言語名文字列(ANSI)を取得
		mxResult = MxPluginPort_Project_MultiLang_GetName(pageIndex, &pname);
		if (!mxResult) {
			return false;
		}

		std::string pageName = std::string(pname);
		list.push_back(pageName);
	}

	return true;
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
	BOOL mxResult = false;
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
		mxResult = MxPluginPort_Project_MultiLang_Add(list[pageIndex].c_str());
		if (!mxResult) {
			return false;
		}

		std::string msg = "LANGUAGE [" + list[pageIndex] + "]: Added";
		this->pLogger->log(msg);
	}

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


bool MultiLangTextController::SetTextProperty(int castNumber, TextData& textData) {
	bool mxResult = false;

	if (this->writeData.flagApplyFontNameToTextCast){
		mxResult = MxPluginPort_CastPropety_SetDataPtr(ct_Text, castNumber, cp_Text_FontName, (void*)textData.fontName.c_str());
		if (!mxResult) {
			return false;
		}
	}

	if (this->writeData.flagApplyFontSizeToTextCast) {
		mxResult = MxPluginPort_CastPropety_SetDataInt(ct_Text, castNumber, cp_Text_FontSize, (int)textData.fontSize);
		if (!mxResult) {
			return false;
		}
	}

	if (this->writeData.flagApplyTextColorToTextCast) {
		int colorValue = (textData.colorR & 0x000000ff)
			+ ((textData.colorG << 8) & 0x0000ff00)
			+ ((textData.colorB << 16) & 0x00ff0000);
		mxResult = MxPluginPort_CastPropety_SetDataInt(ct_Text, castNumber, cp_Text_FontColor, colorValue);
		if (!mxResult) {
			return false;
		}
	}

	if (this->writeData.flagApplyStringToTextCast) {
		bool isUnicodeTextCast = true;
		if (isUnicodeTextCast) {
			mxResult = MxPluginPort_CastPropety_SetDataPtr(ct_Text, castNumber, cp_Text_TextData, (void*)textData.wtext.c_str());
		}
		else {
			mxResult = MxPluginPort_CastPropety_SetDataPtr(ct_Text, castNumber, cp_Text_TextData, (void*)textData.text.c_str());
		}
		if (!mxResult) {
			return false;
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
	int castNumber = 10;
	int resultNumber;
	bool mxResult;
	string castName = "Text10";
	string text10Eng = "Hello\nWorld";
	resultNumber = MxPluginPort_Cast_CreateTextEx(castNumber, (char*)castName.c_str(), set_ANSI);
	mxResult = MxPluginPort_Cast_Text_CreateLanguage(resultNumber, 0);
	mxResult = MxPluginPort_Cast_Text_SetTextDataANSI(resultNumber, 0, text10Eng.c_str());
	mxResult = MxPluginPort_Cast_Text_SetFontColor(resultNumber, 0, 0x0000ff);
	mxResult = MxPluginPort_Cast_Text_SetFontSize(resultNumber, 0, 20);

	castNumber = 11;
	castName = "Text11";
	wstring text11Kor = L"아니\n오";
	resultNumber = MxPluginPort_Cast_CreateTextEx(castNumber, (char*)castName.c_str(), set_UTF);
	mxResult = MxPluginPort_Cast_Text_CreateLanguage(resultNumber, 2);
	mxResult = MxPluginPort_Cast_Text_SetTextDataWIDE(resultNumber, 2, text11Kor.c_str());
	mxResult = MxPluginPort_Cast_Text_SetFontColor(resultNumber, 2, 0x00ff00);
	mxResult = MxPluginPort_Cast_Text_SetFontSize(resultNumber, 2, 28);


}
