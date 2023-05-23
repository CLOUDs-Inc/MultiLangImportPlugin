#include "pch.h"

/// <summary>
/// 内部限定format関数
/// </summary>
/// <typeparam name="...Args"></typeparam>
/// <param name="fmt"></param>
/// <param name="...args"></param>
/// <returns></returns>
template <typename ... Args>
std::string MXFormat(const std::string& fmt, Args ... args)
{
	size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args ...);
	std::vector<char> buf(len + 1);
	std::snprintf(&buf[0], len + 1, fmt.c_str(), args ...);
	return std::string(&buf[0], &buf[0] + len);
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="on">ログ機能OnOff</param>
MultiLangTextController::MultiLangTextController(WriteData& writeData)
{
	this->writeData = writeData;
	this->pLogger = new UnicodeLogger(writeData.flagLogOutput);

	std::string msg = "# Import Date: " + this->pLogger->getLogDateString();
	this->pLogger->log(msg);
	std::wstring wmsg = L"# Import File: " + writeData.importExcelFileFullPathWide;
	this->pLogger->log(wmsg);
	this->pLogger->log("");
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

	result = this->SetProjectMLEnable();
	if (!result) {
		this->pLogger->log(L"[error]Failed to set multi language available.");
		return false;
	}

	// UI側指定の言語名をページとして追加する
	// 言語ページ追加処理
	result = AddPageNames(writeData.languageNameList);
	if (!result) {
		this->pLogger->log(L"[error]Failed to add language pages.");
		return false;
	}

	result = ImportTextDataTable();

	return result;
}


/// <summary>
/// UI側テキストデータのプロジェクトへのインポート開始
/// </summary>
/// <returns>インポート成否</returns>
bool MultiLangTextController::ImportTextDataTable()
{
	int rowCount = (int)this->writeData.textDataTable.size();

	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		bool result = this->ImportTextDataRow(rowIndex, this->writeData.textDataTable[rowIndex]);
		if (!result) {
			return false;
		}
	}

	return true;
}


/// <summary>
/// UI側テキストデータ１行分をプロジェクトへインポート
/// </summary>
/// <param name="rowIndex">行番号</param>
/// <param name="textDataRow">１行データ</param>
/// <returns>成否</returns>
bool MultiLangTextController::ImportTextDataRow(int rowIndex, std::vector<TextData>& textDataRow)
{
	bool result = false;

	int castIndex = -1;
	int cloneCastIndex = -1;

	bool addedCastFlag = false; // 新規追加テキストキャストであることを示すフラグ

	bool isUnicode = this->writeData.flagCreateAsUnicodeTextCast || this->CheckTextDataRowMustBeUTF(textDataRow);

	// サブキャスト使用の是非で処理が分かれる
	// check:option:サブキャスト名を使用する
	if (!this->writeData.flagUseSubcastName)
	{
		// check:option:サブキャスト名を使用する:Off
		// 既存のキャストを検索
		castIndex = FindTextCastNumber(this->writeData.textCastNameListLoneMod[rowIndex]);
		if (castIndex == -1) {
			// 新規テキストキャスト
			
			// check:不明なテキストキャストを新規に追加
			if (this->writeData.flagAddIfTextCastNotFound) {
				// 新規追加するので、新しいキャスト番号を取得する
				castIndex = GetNewTextCastNumber();

				// キャスト番号は新規追加用であることを示すフラグ
				addedCastFlag = true;

				// キャスト名で新規キャストを作成
				result = CreateNewTextCast(castIndex, this->writeData.textCastNameListLoneMod[rowIndex], isUnicode);
				if (!result) {
					return false;
				}
				 
				// インポートログ：追加
				this->pLogger->log(
					MXFormat("CAST [%4d: %s]: Added", castIndex, this->writeData.textCastNameListLoneMod[rowIndex].c_str())
				);
			}
		}
		else {
			// キャストは既存

			// check:既存のテキストキャストを更新しない
			if (this->writeData.flagNotUpdateExistingTextCast) {
				castIndex = -1;
			}

			// インポートログを追加
			if (castIndex != -1) {
				this->pLogger->log(
					MXFormat("CAST [%4d: %s]: Update", castIndex, this->writeData.textCastNameListLoneMod[rowIndex].c_str())
				);
			}
			else {
				this->pLogger->log(
					MXFormat("CAST [%s]: Skipped", this->writeData.textCastNameListLoneMod[rowIndex].c_str())
				);
			}
		}
	}
	else
	{
		// check:option:サブキャスト名を使用する:On

		// check:option:キャスト検索時にサブキャスト名を使用
		if (this->writeData.flagUseSubcastNameWhenSearchingForCast) {
			// サブキャスト名で既存テキストキャストが存在するかチェック
			castIndex = FindTextCastNumber(this->writeData.textCastNameListConjMod[rowIndex]);
		}
		else {
			// 非サブキャスト名で既存テキストキャストが存在するかチェック
			castIndex = FindTextCastNumber(this->writeData.textCastNameListLoneMod[rowIndex]);
			if (-1 == castIndex)
			{
				// check:option:新規キャスト作成時にサブキャスト名を付加
				if (this->writeData.flagAddSubcastNameWhenCreatingANewCast) {
					// サブキャスト名を含んだキャスト名で既存のキャストを再検索
					castIndex = FindTextCastNumber(this->writeData.textCastNameListConjMod[rowIndex]);
				}
			}
			else
			{
				// サブキャスト作成時に元のキャストのクローンとして作成するかどうかを判別
				if (this->writeData.flagAddSubcastNameWhenCreatingANewCast &&
					this->writeData.textCastNameListConjMod[rowIndex] != this->writeData.textCastNameListLoneMod[rowIndex])
				{
					cloneCastIndex = castIndex;
					castIndex = FindTextCastNumber(this->writeData.textCastNameListConjMod[rowIndex]);
				}
			}
		}

		// ここの時点でcastIndex:-1の場合、既存のテキストキャストがないことを示す
		if (-1 == castIndex)
		{
			// check:不明なテキストキャストを新規に追加
			if (this->writeData.flagAddIfTextCastNotFound)
			{
				// 新しいキャスト番号を取得する
				castIndex = GetNewTextCastNumber();

				if (this->writeData.flagAddSubcastNameWhenCreatingANewCast) {
					// サブキャスト名で新規キャストを作成
					result = CreateNewTextCast(castIndex, this->writeData.textCastNameListConjMod[rowIndex], isUnicode);
					if (!result) {
						return false;
					}
				}
				else {
					// キャスト名で新規キャストを作成
					result = CreateNewTextCast(castIndex, this->writeData.textCastNameListLoneMod[rowIndex], isUnicode);
					if (!result) {
						return false;
					}
				}

				// インポートログを追加
				if (cloneCastIndex == -1) {
					std::string castname = this->GetTextCastNameOfProject(castIndex);
					this->pLogger->log(MXFormat("CAST [%4d: %s]: Added", castIndex, castname.c_str()));
				}
				else {
					std::string castname = this->GetTextCastNameOfProject(castIndex);
					std::string cloneCastname = this->GetTextCastNameOfProject(cloneCastIndex);
					this->pLogger->log(
						MXFormat("CAST [%4d: %s]: Added by duplicating cast [%4d: %s]",
							castIndex, castname.c_str(),
							cloneCastIndex, cloneCastname.c_str()
						)
					);
				}

				// キャスト番号は新規追加用であることを示すフラグ
				addedCastFlag = true;
			}
		}
		else
		{
			// テキストキャストが既存
			// check:既存のテキストキャストを更新しない
			if (this->writeData.flagNotUpdateExistingTextCast) {
				castIndex = -1;
			}

			// インポートログを追加
			if (-1 != castIndex) {
				std::string castname = this->GetTextCastNameOfProject(castIndex);
				this->pLogger->log(MXFormat("CAST [%4d: %s]: Update", castIndex, castname.c_str()));
			}
			else {
				if (this->writeData.flagAddSubcastNameWhenCreatingANewCast
					|| this->writeData.flagUseSubcastNameWhenSearchingForCast)
				{
					this->pLogger->log(MXFormat("CAST [%s]: Skipped", this->writeData.textCastNameListConjMod[rowIndex].c_str()));
				}
				else
				{
					this->pLogger->log(MXFormat("CAST [%s]: Skipped", this->writeData.textCastNameListLoneMod[rowIndex].c_str()));
				}
			}

		}
	}

	// 対象のキャストがなければ何もしない
	if (castIndex == -1) {
		return true;
	}

	if (cloneCastIndex != -1) {
		// プロパティコピー元のテキストキャストを取得して内容を複製
		result = CloneTextCast(castIndex, cloneCastIndex);
		if (!result) {
			return result;
		}
	}

	// 指定ターゲットテキストキャストをUnicode化する
	if (isUnicode) {
		// まだUnicodeでなければ
		TTextStringEncodeType encode;
		MxPluginPort_Cast_Text_GetEncode(castIndex, &encode);
		if (encode == set_ANSI) {
			// テキストキャストのエンコードをUTFに変換
			MxPluginPort_CastPropety_SetDataInt(ct_Text, castIndex, cp_Text_StringEncode, set_UTF);
		}
	}

	for (int colIndex = 0; colIndex < textDataRow.size(); colIndex++) {
		result = UpdateTextCastLangPage(castIndex, textDataRow[colIndex], this->writeData.languageNameList[colIndex], isUnicode, cloneCastIndex, addedCastFlag);
		if (!result) {
			return result;
		}
	}

	return result;
}


/// <summary>
/// 既存のテキストキャスト間で文字列以外のプロパティデータをコピーする
/// </summary>
/// <param name="toCastNumber">dstテキストキャスト番号</param>
/// <param name="fromCastNumber">srcテキストキャスト番号</param>
/// <returns>成否</returns>
bool MultiLangTextController::CloneTextCast(int toCastNumber, int fromCastNumber)
{
	bool result = false;
	BOOL mxResult;

	// 言語ページの最大数を取得（言語カウンタのリミット用）
	int langPageMax;
	mxResult = MxPluginPort_Project_MultiLang_GetCount(&langPageMax);
	if (!mxResult) {
		this->pLogger->log("[error]Failed to read language number of project");
		return result;
	}

	// 指定テキストキャストの言語ページを取得
	for (int pageIndex = 0; pageIndex < langPageMax; pageIndex++) {
		bool langAssigned = false;
		mxResult = MxPluginPort_Cast_Text_GetLanguageAssigned(fromCastNumber, pageIndex, &langAssigned);
		if (!mxResult) {
			this->pLogger->log(MXFormat("[error]Failed to check language assignment of CAST[%4d]:page[%d]", fromCastNumber, pageIndex));
			return result;
		}

		// from側に言語ページがなければスキップ
		if (!langAssigned) {
			continue;
		}

		mxResult = MxPluginPort_Cast_Text_GetLanguageAssigned(toCastNumber, pageIndex, &langAssigned);
		if (!mxResult) {
			this->pLogger->log(MXFormat("[error]Failed to check language assignment of CAST[%4d]:page[%d]", toCastNumber, pageIndex));
			return result;
		}

		// to側に言語ページがなければページを追加する
		if (!langAssigned) {
			MxPluginPort_Cast_Text_CreateLanguage(toCastNumber, pageIndex);
		}

		// プロパティをコピーする
		CloneTextCastPage(toCastNumber, pageIndex, fromCastNumber, pageIndex, true, true, true);
	}
	return true;
}


void MultiLangTextController::CloneTextCastPage(
	int toCastNumber, int toLangPage, int fromCastNumber, int fromLangPage,
	bool enableFontName, bool enableFontSize, bool enableFontColor
)
{
	BOOL mxResult;
	bool flag;

	// プロパティをコピーする
	
	if (enableFontName) {
		// フォント名
		char* fontName;
		mxResult = MxPluginPort_Cast_Text_GetFontName(fromCastNumber, fromLangPage, (const char**)&fontName);
		if (mxResult) {
			MxPluginPort_Cast_Text_SetFontName(toCastNumber, toLangPage, fontName);
		}
		// スタイル
		TTextFontStyleType style;
		mxResult = MxPluginPort_Cast_Text_GetFontStyle(fromCastNumber, fromLangPage, &style);
		if (mxResult) {
			MxPluginPort_Cast_Text_SetFontStyle(toCastNumber, toLangPage, style);
		}
		// charset
		int charsetValue;
		mxResult = MxPluginPort_Cast_Text_GetFontCharSet(fromCastNumber, fromLangPage, &charsetValue);
		if (mxResult) {
			MxPluginPort_Cast_Text_SetFontCharSet(toCastNumber, toLangPage, charsetValue);
		}
	}
	if (enableFontSize) {
		// サイズ
		int sizeVal;
		mxResult = MxPluginPort_Cast_Text_GetFontSize(fromCastNumber, fromLangPage, &sizeVal);
		if (mxResult) {
			MxPluginPort_Cast_Text_SetFontSize(toCastNumber, toLangPage, sizeVal);
		}
		// 高さ
		int height;
		// Delphiの仕様により、符号が反転する
		// Point値が正=>Pixel値が負。Pixel値が正=>Point値が負。
		mxResult = MxPluginPort_Cast_Text_GetFontHeight(fromCastNumber, fromLangPage, &height);
		if (mxResult) {
			MxPluginPort_Cast_Text_SetFontHeight(toCastNumber, toLangPage, height);
		}
	}
	if (enableFontColor) {
		// 色
		int color;
		mxResult = MxPluginPort_Cast_Text_GetFontColor(fromCastNumber, fromLangPage, &color);
		if (mxResult) {
			MxPluginPort_Cast_Text_SetFontColor(toCastNumber, toLangPage, color);
		}
		// 背景色
		mxResult = MxPluginPort_Cast_Text_GetBackColor(fromCastNumber, fromLangPage, &color);
		if (mxResult) {
			MxPluginPort_Cast_Text_SetBackColor(toCastNumber, toLangPage, color);
		}
	}

	// 透明
	bool transparent;
	mxResult = MxPluginPort_Cast_Text_GetTransparent(fromCastNumber, fromLangPage, &transparent);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetTransparent(toCastNumber, toLangPage, transparent);
	}
	// text alpha enabled
	bool textAlpha;
	mxResult = MxPluginPort_Cast_Text_GetAlphaEnabled(fromCastNumber, fromLangPage, &textAlpha);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetAlphaEnabled(toCastNumber, toLangPage, textAlpha);
	}
	// text anti-aliasing
	bool antiAlias;
	mxResult = MxPluginPort_Cast_Text_GetAntialias(fromCastNumber, fromLangPage, &antiAlias);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetAntialias(toCastNumber, toLangPage, antiAlias);
	}
	// pickup disabled
	mxResult = MxPluginPort_Cast_Text_GetClickEnabled(fromCastNumber, fromLangPage, &flag);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetClickEnabled(toCastNumber, toLangPage, flag);
	}
	// text align
	TTextAlignment align;
	mxResult = MxPluginPort_Cast_Text_GetAlignment(fromCastNumber, fromLangPage, &align);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetAlignment(toCastNumber, toLangPage, align);
	}
	// Z position
	mxResult = MxPluginPort_Cast_Text_GetBackward(fromCastNumber, fromLangPage, &flag);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetBackward(toCastNumber, toLangPage, flag);
	}
	// fix size text
	mxResult = MxPluginPort_Cast_Text_GetFixSize(fromCastNumber, fromLangPage, &flag);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetFixSize(toCastNumber, toLangPage, flag);
	}
	// item distance
	int distance;
	mxResult = MxPluginPort_Cast_Text_GetItemDistance(fromCastNumber, fromLangPage, &distance);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetItemDistance(toCastNumber, toLangPage, distance);
	}
	// fix width
	int width;
	mxResult = MxPluginPort_Cast_Text_GetAlignmentWidth(fromCastNumber, fromLangPage, &width);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetAlignmentWidth(toCastNumber, toLangPage, width);
	}
	// center X
	int centerX;
	mxResult = MxPluginPort_Cast_Text_GetCenterX(fromCastNumber, fromLangPage, &centerX);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetCenterX(toCastNumber, toLangPage, centerX);
	}
	// center Y
	int centerY;
	mxResult = MxPluginPort_Cast_Text_GetCenterY(fromCastNumber, fromLangPage, &centerY);
	if (mxResult) {
		MxPluginPort_Cast_Text_SetCenterY(toCastNumber, toLangPage, centerY);
	}
}


bool MultiLangTextController::UpdateTextCastLangPage(int castNumber, TextData& textData, std::string& langPageName, bool isUnicode, int cloneIndex, bool addedCastFlag)
{
	BOOL mxResult = FALSE;
	bool result = false;
	bool flagNewPage = false; // 言語ページ作成フラグ
	// 言語ページを作成

	// 言語ページ番号を取得
	int pageNumber = this->GetProjectLangNumber(langPageName);

	if (pageNumber == -1) {
		return true;
	}

	// 言語ページを追加
	result = CreateLangPageToTextCast(castNumber, pageNumber, addedCastFlag, flagNewPage);
	if (!result) {
		return result;
	}


	bool isCloneTextLangAssigned = false;
	if (-1 != cloneIndex) {
		MxPluginPort_Cast_Text_GetLanguageAssigned(cloneIndex, pageNumber, &isCloneTextLangAssigned);
	}
	// テキストキャストのプロパティを更新
	// クローン元のテキストキャストに言語がassigned checkされているか
	if (isCloneTextLangAssigned) { 
		// コピー元のテキストキャストと同じ値を設定
		CloneTextCastPage(castNumber, pageNumber, cloneIndex, pageNumber, true, true, true);
	}
	else {
		// 先頭ページのプロパティを継承
		if (pageNumber != 0 && this->writeData.flagInheritPropertiesOfTheFirstLangPage) {
			if (!this->writeData.flagInheritOnlyNewLangPage || flagNewPage) {
				CloneTextCastPage(
					castNumber, pageNumber, castNumber, 0,
					!this->writeData.flagApplyFontNameToTextCast,
					!this->writeData.flagApplyFontSizeToTextCast,
					!this->writeData.flagApplyTextColorToTextCast
				);
			}
		}

		// フォントの更新
		// check:フォント名をテキストキャストに反映
		if (this->writeData.flagApplyFontNameToTextCast) {
			if (!textData.fontName.empty()) {
				// フォント名を設定
				mxResult = MxPluginPort_Cast_Text_SetFontName(castNumber, pageNumber, textData.fontName.c_str());
				if (!mxResult) {
					this->pLogger->log(
						MXFormat("[error]Failed to set font name[%s] to Cast[%d],Page[%d]", textData.fontName.c_str(), castNumber, pageNumber)
					);
					return false;
				}
			}
		}
		// check:フォントサイズをテキストキャストに反映
		if (this->writeData.flagApplyFontSizeToTextCast) {
			mxResult = MxPluginPort_Cast_Text_SetFontSize(castNumber, pageNumber, (int)textData.fontSize);
			if (!mxResult) {
				this->pLogger->log(
					"[error]Failed to set font size to Cast[" + ::to_string(castNumber) + "],Page[" + ::to_string(pageNumber) + "]"
				);
				return false;
			}
		}
		// check:文字色をテキストキャストに反映
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

			int backColor;
			mxResult = MxPluginPort_Cast_Text_GetBackColor(castNumber, pageNumber, &backColor);
			if (!mxResult) {
				this->pLogger->log(
					"[error]Failed to get back color to Cast[" + ::to_string(castNumber) + "],Page[" + ::to_string(pageNumber) + "]"
				);
				return false;
			}

			// フォント色と背景色が同一の時、背景色を調整する
			if (colorValue == backColor) {
				backColor = ChooseBackColor(colorValue);
				MxPluginPort_Cast_Text_SetBackColor(castNumber, pageNumber, backColor);
			}
		}
	}

	// テキストデータの更新
	if (this->writeData.flagApplyStringToTextCast)
	{
		BOOL mxResult;
		if (isUnicode) {
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
/// 新規テキストキャストを指定番号で作成する
/// </summary>
/// <param name="castNumber">新規キャスト番号</param>
/// <param name="castname">新規キャスト名</param>
/// <param name="isUnicode">Unicodeフラグ</param>
/// <returns></returns>
bool MultiLangTextController::CreateNewTextCast(int castNumber, std::string& castname, bool isUnicode)
{
	int resultNumber;

	if (isUnicode) {
		resultNumber = MxPluginPort_Cast_CreateTextEx(castNumber, (char*)castname.c_str(), set_UTF);
	}
	else {
		resultNumber = MxPluginPort_Cast_CreateTextEx(castNumber, (char*)castname.c_str(), set_ANSI);
	}

	// テキストキャスト生成エラーを確認
	if (castNumber != resultNumber) {
		this->pLogger->log("[error]Failed to create new text cast[" + castname + "]" + (isUnicode ? "[UTF]" : "[ANSI]"));
		return false;
	}

	return true;
}


/// <summary>
/// 番号指定のテキストキャストにプロジェクトの指定の言語ページを追加する（既存の場合は成功）
/// </summary>
/// <param name="castNumber">書き込み先テキストキャスト番号</param>
/// <param name="pageNumber">プロジェクト言語ページ番号</param>
/// <param name="addedCastFlag">対象テキストキャストが新規追加されたものかどうか</param>
/// <param name="createPageFlag">[out]新規ページ作成フラグ</param>
/// <returns>成否</returns>
bool MultiLangTextController::CreateLangPageToTextCast(int castNumber, int pageNumber, bool addedCastFlag, bool& createPageFlag)
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

	if (exist)
	{
		// 既にテキストキャストに指定の言語ページがある場合は、後続の「テキストキャストに言語ページ生成」は行わない
		// ただしテキストキャスト新規作成時にはデフォルトで第０ページが存在するので、その場合は
		// スキップしながら言語ページを追加したものとみなす
		if (pageNumber == 0 && addedCastFlag) {
			// [out]
			createPageFlag = true;
		}
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
/// キャスト番号によるテキストキャスト名の取得
/// </summary>
/// <param name="castNumber">キャスト番号</param>
/// <returns>キャスト名</returns>
string MultiLangTextController::GetTextCastNameOfProject(int castNumber)
{
	// スクリプトキャスト名の取得
	char castname[MAX_PATH] = { 0 };
	MxPluginPort_Cast_GetCastName(ct_Text, castNumber, castname, MAX_PATH);
	std::string castnameString = std::string(castname);
	return castnameString;
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
int MultiLangTextController::GetProjectLangNumber(std::string targetName)
{
	int pageNumber = -1;

	// SDK側言語リストからページ名で検索しページ番号を取得
	BOOL mxResult;

	// プロジェクト内の言語数を取得
	int pageCount;
	mxResult = MxPluginPort_Project_MultiLang_GetCount(&pageCount);
	if (!mxResult) {
		this->pLogger->log(L"[error]Failed to get count of language pages of project.");
		return -1;
	}

	// プロジェクト内言語のそれぞれに対して。
	for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
	{
		char* pname = nullptr;
		// 言語名文字列(ANSI)を取得
		mxResult = MxPluginPort_Project_MultiLang_GetName(pageIndex, &pname);
		if (!mxResult) {
			this->pLogger->log(L"[error]Failed to get name of language page of number " + to_wstring(pageIndex));
			return -1;
		}
		
		std::string pageName = std::string(pname);
		if (pageName == targetName) {
			// 見つかった
			pageNumber = pageIndex;
			break;
		}
	}

	return pageNumber;
}

/// <summary>
/// プロジェクトに使用したい言語ページを追加でセットする
/// 既存ページと重複する場合はスキップで成功とする
/// </summary>
/// <param name="list">追加使用したい言語ページ</param>
/// <returns>ページ設定の成否</returns>
bool MultiLangTextController::AddPageNames(std::vector<std::string>& langNameList)
{
	// デフォルト言語とする言語ページを設定
	if (!this->writeData.defaultLanguageName.empty())
	{
		// デフォルト言語を設定できるのは、多言語未使用時か設定済み言語ページがデフォルト０の時のみ
		// 言語ページ0の言語名を更新する
		MxPluginPort_Project_MultiLang_SetName(0, this->writeData.defaultLanguageName.c_str());
		this->pLogger->log(MXFormat("LANGUAGE [%s]: Set Default", this->writeData.defaultLanguageName.c_str()));
	}

	// 言語ページの更新
	for (int uiLangIndex = 0; uiLangIndex < langNameList.size(); uiLangIndex++)
	{
		int projLangNumber = this->GetProjectLangNumber(langNameList[uiLangIndex]);
		if(projLangNumber == -1 && this->writeData.flagAddIfLanguagePageNotFound)
		{
			MxPluginPort_Project_MultiLang_Add(langNameList[uiLangIndex].c_str());
			this->pLogger->log(MXFormat("LANGUAGE [%s]: Added", langNameList[uiLangIndex].c_str()));
		}
	}

	return true;
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


double MultiLangTextController::color_lum(int c)
{
	double tmp = c / 255.0;
	if (tmp <= 0.03828) {
		return tmp / 12.92;
	}
	else {
		return std::pow((tmp + 0.0055) / 1.055, 2.4);
	}
}

int MultiLangTextController::ChooseBackColor(int color) {
	double lw = 1.0;
	double lb = 0.0;
	double r = color_lum(color & 0x000000ff);
	double g = color_lum((color >> 8) & 0x000000ff);
	double b = color_lum((color >> 16) & 0x000000ff);
	double l = r * 0.2126f + g * 0.7152f + b * 0.0722;

	double cw = (lw * 0.05) / (l + 0.05);
	double cb = (l * 0.05) / (lb + 0.05);
	if (cw < cb) {
		return 0x00000000; // black
	}
	else {
		return 0x00ffffff; // white
	}
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
