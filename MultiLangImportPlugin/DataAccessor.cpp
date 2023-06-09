#include "pch.h"

DataAccessor::DataAccessor(HINSTANCE hinstDLL, LPVOID lpvReserved)
{
	this->hinstDLL = hinstDLL;
	this->lpvReserved = lpvReserved;
}

string DataAccessor::GetDirectoryFromPath(const string& filepath) {

	char buffer[MAX_PATH];
	GetFullPathNameA(filepath.c_str(), MAX_PATH, buffer, nullptr);
	PathRemoveFileSpecA(buffer);
	string directory = string(buffer);
	return directory;
}


/// <summary>
/// SDKのプロジェクト情報の取得・格納
/// </summary>
/// <param name="aatData">データ管理オブジェクト</param>
/// <returns>処理成否</returns>
bool DataAccessor::GetProjectInfo(SdkData& data)
{
	// プロジェクトファイルパスを取得
	char* pProjectPath;
	pProjectPath = MxPluginPort_Project_GetContentsPath();
	if (pProjectPath == NULL) {
		return false;
	}

	// プロジェクト名を取得
	char* pProjectName;
	pProjectName = MxPluginPort_Project_GetContentsName();
	if (pProjectName == NULL) {
		return false;
	}

	// 多言語使用設定をプロジェクトから取得
	BOOL enabled;
	BOOL mxResult = MxPluginPort_Project_MultiLang_GetEnabled(&enabled);
	if (!mxResult) {
		return false;
	}

	// 多言語使用ページ数をプロジェクトから取得
	int pageNumber = 0;
	mxResult = MxPluginPort_Project_MultiLang_GetCount(&pageNumber);
	if (!mxResult) {
		return false;
	}

	// プロジェクトファイルパスを保持
	data.projectPath = string(pProjectPath);
	// プロジェクト名を保持
	data.projectName = string(pProjectName);
	// 多言語使用状態を保持
	data.multiLangEnabled = enabled ? true : false;
	// 多言語使用ページ数を保持
	data.langPageNumber = pageNumber;

	return true;
}

/// <summary>
/// テキストキャストデータ書き込み
/// </summary>
/// <param name="writeData">書き込み管理データ</param>
/// <returns>処理成否</returns>
bool DataAccessor::SetTextCastDataInMultiLanguage(WriteData& writeData, SdkData& sdkData)
{
	bool result = true;

	string logDir = GetDirectoryFromPath(sdkData.projectPath);


	MultiLangTextController mlTextController(writeData);
	result = mlTextController.ImportTextData();
	return result;
}
