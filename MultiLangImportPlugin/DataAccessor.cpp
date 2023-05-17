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
	int mxResult;

	string logDir = GetDirectoryFromPath(sdkData.projectPath);
	// ロガーを取得
	//SingleLogger* logger = SingleLogger::getLogger()
	// ログ：日時


	// ログ：インポートExcelファイルパス情報


	MultiLangTextController mlTextController(writeData);

	result = mlTextController.ImportTextData();

	// tttest
	//mlTextController.TestWriteTextCast();
	return result;
}

//bool DataAccessor::WriteFontColorTableScript(WriteData& writeData)
//{
//	bool result = true;
//	int mxResult;
//	int castNo;
//
//	// 同じ名前のスクリプトキャストの有無を確認する
//	mxResult = MxPluginPort_Cast_FindCast(ct_Script, (char*)writeData.scriptName.c_str());
//	if (mxResult >= 0) {
//		// 見つかった
//		// キャスト番号を設定
//		castNo = mxResult;
//	}
//	else
//	{
//		// キャストが見つからない
//
//		// スクリプトキャストの（ブランクも含んだ）数を取得する
//		mxResult = MxPluginPort_Cast_GetCastCount(ct_Script);
//		if (mxResult < 0) {
//			// キャスト番号がない
//			result = false;
//			goto FUNC_ERROR;
//		}
//
//		// キャスト番号として末尾に一つブランクを空けた番号を指定する
//		castNo = mxResult + 1;
//
//		// スクリプトキャストの作成
//		mxResult = MxPluginPort_Cast_CreateScript(castNo, (char*)writeData.scriptName.c_str());
//		if (mxResult < 0) {
//			// キャスト作成失敗
//			result = false;
//			goto FUNC_ERROR;
//		}
//	}
//
//	// コード書き込み
//	mxResult = MxCast_Script_SetCode(castNo, (void*)writeData.tableScriptCode.c_str());
//	if (mxResult < 0) {
//		result = false;
//		goto FUNC_ERROR;
//	}
//
//
//FUNC_ERROR:
//
//	return result;
//}

