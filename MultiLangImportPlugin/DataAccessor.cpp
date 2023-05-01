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

	// プロジェクトファイルパスを保持
	data.projectPath = string(pProjectPath);
	// プロジェクト名を保持
	data.projectName = string(pProjectName);

	return true;
}

/// <summary>
/// デフォルト言語設定
/// </summary>
/// <param name="writeData">書き込み管理データ</param>
/// <returns>処理成否</returns>
bool DataAccessor::SetDefaultLanguage(WriteData& writeData)
{
	bool result = true;
	int mxResult;

	// デフォルト言語が設定されていなければ(-1)、trueで終了
	if (writeData.selectedLanguageIndex < 0) {
		return result;
	}

	// デフォルト言語インデックス
	int defaultLangIndex = writeData.selectedLanguageIndex;
	
	// デフォルト言語設定


	return result;
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



	MultiLangTextController mlTextController;

	// 言語ページ追加処理の有無確認
	if (writeData.flagAddIfLanguagePageNotFound)
	{
		// 追加言語のリストを作成（サブキャスト用としているExcel列データを外すため）
		vector<string> appendPageNameList;
		for (size_t index = 0; index < writeData.languageNameList.size(); index++)
		{
			// サブキャスト名使用Onなら、サブキャストに使用した列のページ名は追加しない
			if (writeData.flagUseSubcastName && writeData.subcastNameIndex == (int)index)
			{
				continue;
			}

			appendPageNameList.push_back(writeData.languageNameList[index]);
		}

		// 言語ページ追加処理
		mlTextController.SetPageNames(appendPageNameList);
		
		// ログ：追加言語


	}



	// キャスト毎追加処理
	// CastNum=MxPluginPort_Cast_CreateText(CastNum,NULL);

	// 既存同一キャスト名検索

	// キャスト追加 or 参照

	// 文字コード指定

	// 言語ページ指定

	// テキスト

	// フォント名

	// フォントサイズ

	// フォント色(RGB)

	// フォントスタイル










	// キャスト毎追加処理ここまで


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

