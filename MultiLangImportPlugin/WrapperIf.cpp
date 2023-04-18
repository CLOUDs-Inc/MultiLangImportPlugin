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
	writeData.selectedLanguageIndex = DownloadInteger("DefaultLanguageIndex");
	writeData.subcastNameIndex = DownloadInteger("SubcastNameIndex");
	int textCastNameCount = DownloadInteger("TextCastNameCount");
	int languageNameCount = DownloadInteger("LanguageNameCount");

	bool flagAddIfLangPageNotFound = DownloadFlag("AddIfLangPageNotFound");
	bool flagUseSubcastName = DownloadFlag("UseSubcastName");

	// テキストキャスト名リストをUIから下ろす
	char** textCastNameArray = DownloadStringArray("TextCastNameArray");
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++)
	{
		std::string textCastName = std::string(textCastNameArray[castIndex]);

		// テキストキャスト名リストに保持
		writeData.textCastNameList.push_back(textCastName);
	}

	// テキストキャスト名リストのメモリ解放
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++) {
		delete[] textCastNameArray[castIndex];
	}
	delete[] textCastNameArray;



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

	for (int rowIndex = 0; rowIndex < textCastNameCount; rowIndex++) {
		TextData* textDataRow = textDataTable[rowIndex];

		for (int colIndex = 0; colIndex < languageNameCount; colIndex++) {
			TextData textData = textDataRow[colIndex];
		}
	}

	// 多言語インポートデータを保持
	// CODE HERE




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
	dataAccessor.GetProjectInfo(sdkData);

	// (char*に切り替えた)プロジェクト情報を.NET側に転送
	UploadProjectInfo(sdkData.projectPath.c_str(), sdkData.projectName.c_str());

	// SDKからテキストキャスト名を取得し、.net側にアップする
	dataAccessor.GetTextCastNames(sdkData);

	// vector<string>からvector<char*>に変換
	vector<char*> namePointers;
	for (size_t idx = 0; idx < sdkData.textCastNames.size(); idx++) {
		char* pc = (char*)sdkData.textCastNames[idx].c_str();
		namePointers.push_back(pc);
	}

	// 送信用テキストキャスト名ポインタ配列
	char** sentNamePointers = nullptr;
	// テキストキャスト名の実データを割り当て
	if (0 < namePointers.size()) {
		sentNamePointers = &(namePointers[0]);
	}


	// UI側に生成処理開始を依頼
	process_result = BeginProcess();
	if (!process_result) {
		return;
	}


	// SDKへの書き込み用データ
	WriteData writeData;

	// UIのデータを全て下ろして書き込み用データ領域に移動
	DownloadAllUIData(writeData);

	

	// 出力スクリプトキャスト名取得
	//char* pScriptName = DownloadString("DownloadFontColorTableScriptName");
	//writeData.scriptName = string(pScriptName);
	//delete[] pScriptName;

	// 出力スクリプトキャストコード取得
	//char* pScriptCode = DownloadString("DownloadFontColorTableScriptCode");
	//writeData.tableScriptCode = string(pScriptCode);
	//delete[] pScriptCode;

	// 出力スクリプトキャストコードをSDKで書き込み
	//bool write_result = dataAccessor.WriteFontColorTableScript(writeData);
	bool write_result = false;
	if (!write_result) {
		MessageBox(this->hWnd, L"Writing script cast failed.", L"Error", MB_OK);
	}
	else {
		MessageBox(this->hWnd, L"Writing script cast succeeded.", L"Error", MB_OK);
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
