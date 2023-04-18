#include "pch.h"

DataAccessor::DataAccessor(HINSTANCE hinstDLL, LPVOID lpvReserved)
{
	this->hinstDLL = hinstDLL;
	this->lpvReserved = lpvReserved;
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

	// プロジェクトファイルパスを保持
	data.projectPath = string(pProjectPath);
	// プロジェクト名を保持
	data.projectName = string(pProjectName);

	return true;
}

void DataAccessor::GetTextCastNames(SdkData& data)
{
	const int CAST_TYPE = ct_Text;
	int api_ret = 0;

	data.textCastNames.clear();

	// テキストキャストの（ブランクも含んだ）数を取得する
	data.textCastCount = MxPluginPort_Cast_GetCastCount(CAST_TYPE);

	// キャスト番号の最大値までキャスト番号を０からインクリメントしながら走査
	for (int castIndex = 0; castIndex < data.textCastCount; castIndex++)
	{
		// テキストキャスト名の取得
		char name_buffer[MAX_PATH] = { 0 };

		api_ret = MxPluginPort_Cast_GetCastName(CAST_TYPE, castIndex, name_buffer, MAX_PATH);

		// テキストキャスト欄の空欄も把握する必要があるので、
		// 取得に失敗した場合、長さ０の文字列とする

		string castname = string(name_buffer);
		data.textCastNames.push_back(castname);
	}

	return;
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
