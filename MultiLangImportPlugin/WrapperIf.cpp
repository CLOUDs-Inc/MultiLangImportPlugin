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

	PROC_ATTACH(DownloadString, PProcDownloadString, hModule, result, INIT_ERROR);

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

	// 出力スクリプトキャスト名取得
	char* pScriptName = DownloadString("DownloadFontColorTableScriptName");
	writeData.scriptName = string(pScriptName);
	delete[] pScriptName;

	// 出力スクリプトキャストコード取得
	char* pScriptCode = DownloadString("DownloadFontColorTableScriptCode");
	writeData.tableScriptCode = string(pScriptCode);
	delete[] pScriptCode;

	// 出力スクリプトキャストコードをSDKで書き込み
	bool write_result = dataAccessor.WriteFontColorTableScript(writeData);
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
