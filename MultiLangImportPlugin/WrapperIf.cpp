#include "pch.h"

//--------------------
// Wrapper DLLとのIF
//--------------------
WrapperIf::WrapperIf(HWND hWnd, HINSTANCE hinstDLL, LPVOID lpvReserved)
{
	this->hWnd = hWnd;
	this->hinstDLL = hinstDLL;
	this->lpvReserved = lpvReserved;
}

/// <summary>
/// UIからのデータ引き出し処理まとめ
/// </summary>
/// <param name="writeData">書き込み用データ保持領域</param>
void WrapperIf::DownloadAllUIData(WriteData& writeData)
{
	// デフォルト言語名称
	char* pDefaultLangName = DownloadString("DownloadDefaultLanguageName");
	writeData.defaultLanguageName = std::string(pDefaultLangName);
	delete[] pDefaultLangName;
	// サブキャスト扱い列インデックス
	writeData.subcastNameIndex = DownloadInteger("SubcastNameIndex");

	// インポートExcelファイルフルパス文字列
	char* pExcelFullPathStr = DownloadString("DownloadImportExcelFilePath");
	writeData.importExcelFileFullPath = std::string(pExcelFullPathStr);
	delete[] pExcelFullPathStr;
	// インポートExcelファイルフルパス文字列（ワイド）
	wchar_t* pExcelFullPathWStr = DownloadWString("DownloadImportExcelFilePath");
	writeData.importExcelFileFullPathWide = std::wstring(pExcelFullPathWStr);
	delete[] pExcelFullPathWStr;

	// Apply languages and casts設定 =============
	writeData.flagAddIfLanguagePageNotFound = DownloadFlag("AddIfLangPageNotFound");
	writeData.flagAddIfTextCastNotFound = DownloadFlag("AddIfTextCastNotFound");
	writeData.flagCreateAsUnicodeTextCast = DownloadFlag("CreateAsUnicodeTextCast");
	writeData.flagNotUpdateExistingTextCast = DownloadFlag("NotUpdateExistingTextCast");
	writeData.flagInheritPropertiesOfTheFirstLangPage = DownloadFlag("InheritPropertiesOfTheFirstLangPage");
	writeData.flagInheritOnlyNewLangPage = DownloadFlag("InheritOnlyNewLangPage");

	// Apply properties設定 ======================
	writeData.flagApplyFontNameToTextCast = DownloadFlag("ApplyFontName");
	writeData.flagApplyFontSizeToTextCast = DownloadFlag("ApplyFontSize");
	writeData.flagApplyTextColorToTextCast = DownloadFlag("ApplyTextColor");
	writeData.flagApplyStringToTextCast = DownloadFlag("ApplyString");

	// ロギング設定 ==============================
	writeData.flagLogOutput = DownloadFlag("LogOutput");

	// サブキャスト設定 ==========================
	writeData.flagUseSubcastName = DownloadFlag("UseSubcastName");
	writeData.flagUseSubcastNameWhenSearchingForCast = DownloadFlag("UseSubcastNameWhenSearchingForCast");
	writeData.flagAddSubcastNameWhenCreatingANewCast = DownloadFlag("AddSubcastNameWhenCreatingANewCast");
	writeData.flagUseUnderscoreForConjunctionInSubcastName = DownloadFlag("FlagUseUnderscoreForConjunctionInSubcastName");
	char* pConjunctionStr = DownloadString("DownloadSubcastConjunctionString");
	writeData.conjunctionString = std::string(pConjunctionStr);
	delete[] pConjunctionStr;

	int textCastNameCount = DownloadInteger("TextCastNameCount");
	int languageNameCount = DownloadInteger("LanguageNameCount");

	// テキストキャスト名リスト（サブキャスト加工なし）をUIから下ろす
	char** textCastNameArrayLoneMod = DownloadStringArray("TextCastNameArrayLoneMod");
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++)
	{
		std::string textCastName = std::string(textCastNameArrayLoneMod[castIndex]);

		// テキストキャスト名リストに保持
		writeData.textCastNameListLoneMod.push_back(textCastName);
	}

	// テキストキャスト名リストのメモリ解放
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++) {
		delete[] textCastNameArrayLoneMod[castIndex];
	}
	delete[] textCastNameArrayLoneMod;


	// サブキャスト部分名リストをUIから下ろす
	char** subPartNameArrayMod = DownloadStringArray("SubPartNameArrayMod");
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++)
	{
		std::string textCastName = std::string(subPartNameArrayMod[castIndex]);

		// テキストキャスト名リストに保持
		writeData.subPartNameListMod.push_back(textCastName);
	}

	// テキストキャスト名リストのメモリ解放
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++) {
		delete[] subPartNameArrayMod[castIndex];
	}
	delete[] subPartNameArrayMod;


	// テキストキャスト名リスト（サブキャスト加工済み）をUIから下ろす
	char** textCastNameArrayConjMod = DownloadStringArray("TextCastNameArrayConjMod");
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++)
	{
		std::string textCastName = std::string(textCastNameArrayConjMod[castIndex]);

		// テキストキャスト名リストに保持
		writeData.textCastNameListConjMod.push_back(textCastName);
	}

	// テキストキャスト名リストのメモリ解放
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++) {
		delete[] textCastNameArrayConjMod[castIndex];
	}
	delete[] textCastNameArrayConjMod;



	// 言語名リストをUIから下ろす
	char** languageNameArray = DownloadStringArray("LanguageNameArray");
	for (int langIndex = 0; langIndex < languageNameCount; langIndex++)
	{
		std::string languageName = std::string(languageNameArray[langIndex]);

		// 言語名リストに保持
		writeData.languageNameList.push_back(languageName);
	}

	// 言語名リストのメモリ解放
	for (int langIndex = 0; langIndex < languageNameCount; langIndex++) {
		delete[] languageNameArray[langIndex];
	}
	delete[] languageNameArray;



	// 多言語インポートテキストデータをUIから下ろす
	TextData** textDataTable = DownloadTextDataTable();

	// 多言語インポートデータを保持
	for (int rowIndex = 0; rowIndex < textCastNameCount; rowIndex++) {
		TextData* textDataRow = textDataTable[rowIndex];

		vector<TextData> textDataRowVector;
		for (int colIndex = 0; colIndex < languageNameCount; colIndex++) {
			TextData textData = textDataRow[colIndex];
			textDataRowVector.push_back(textData);
		}
		writeData.textDataTable.push_back(textDataRowVector);
	}

	// 多言語インポートテキストデータのメモリ解放
	for (int rowIndex = 0; rowIndex < textCastNameCount; rowIndex++)
	{
		// 一行ずつ解放
		delete[] textDataTable[rowIndex];
	}
	// テーブル全体を解放
	delete[] textDataTable;
}



/// <summary>
/// 初期化処理
/// </summary>
/// <returns>成否</returns>
bool WrapperIf::init()
{
	bool result = true;

	// wrapper.dllのロード LoadLibrary
	// -------------------------------
	wchar_t ModulePath[MAX_PATH + 1];
	GetModuleFileName(hinstDLL, ModulePath, MAX_PATH);

	wchar_t* slash_pos = wcsrchr(ModulePath, '\\');
	*slash_pos = 0;

	// Plug-in DLLのファイルパスをラッパーDLLに変換
	wcscat_s(ModulePath, MAX_PATH, MANAGED_WRAPPER_DLL);

	// ModulePathチェック
	size_t pathSize = wcslen(ModulePath) + 1;
	size_t convertedChars = 0;
	char* pathStr = new char[pathSize * 2];
	wcstombs_s(&convertedChars, pathStr, pathSize * 2, ModulePath, _TRUNCATE);
	delete[] pathStr;

	// DLLファイルのロード
	hModule = LoadLibrary(ModulePath);
	if (hModule == NULL) {
		MessageBox(this->hWnd, L"Wrapper DLL read failed.", L"Error", MB_OK);
		result = false;
		goto INIT_ERROR;
	}

	// DLLの関数アタッチ
	PROC_ATTACH(CreateWrapper, PProcCreateWrapper, hModule, result, INIT_ERROR);
	PROC_ATTACH(BeginProcess, PProcBeginProcess, hModule, result, INIT_ERROR);

	PROC_ATTACH(UploadProjectInfo, PProcUploadProjectInfo, hModule, result, INIT_ERROR);

	PROC_ATTACH(DownloadTextDataTable, PProcDownloadTextDataTable, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadStringArray, PProcDownloadStringArray, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadString, PProcDownloadString, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadWString, PProcDownloadWString, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadInteger, PProcDownloadInteger, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadFloat, PProcDownloadFloat, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadFlag, PProcDownloadFlag, hModule, result, INIT_ERROR);

INIT_ERROR:

	return result;
}

/// <summary>
/// 自動生成ツール処理実行
/// </summary>
void WrapperIf::execute()
{
	BOOL result = TRUE;

	bool create_wrapper_result = false;
	bool process_result = false;

	// CreateWrapper
	create_wrapper_result = CreateWrapper();
	if (!create_wrapper_result) {
		MessageBox(this->hWnd, L"GUI DLL read failed.", L"Error", MB_OK);
		return;
	}

	// SDKアクセスオブジェクト
	DataAccessor dataAccessor(hinstDLL, lpvReserved);

	// SDKからプロジェクト情報を取得し、.net側にアップする
	process_result = dataAccessor.GetProjectInfo(sdkData);
	if (!process_result) {
		return;
	}

	// (char*に切り替えた)プロジェクト情報を.NET側に転送
	UploadProjectInfo(sdkData.projectPath.c_str(), sdkData.projectName.c_str(), sdkData.multiLangEnabled, sdkData.langPageNumber);


	// UI側に生成処理開始を依頼
	process_result = BeginProcess();
	if (!process_result) {
		return;
	}


	// SDKへの書き込み用データ
	WriteData writeData;

	// UIのデータを全て下ろして書き込み用データ領域に移動
	DownloadAllUIData(writeData);

	// 多言語テキストキャストデータをSDKで書き込み
	bool write_result = dataAccessor.SetTextCastDataInMultiLanguage(writeData, sdkData);
	//bool write_result = true;
	if (write_result) {
		MessageBox(this->hWnd, L"Multi-language text casts import succeeded.", L"Error", MB_OK);
	}
	else {
		MessageBox(this->hWnd, L"Multi-language text casts import failed.", L"Error", MB_OK);
	}

	return;
}


/// <summary>
/// Wrapper IFクローズ処理
/// </summary>
void WrapperIf::cleanUp() {

	// dllのアンロード FreeLibrary
	if (hModule != NULL)
		FreeLibrary(hModule);

	return;
}
