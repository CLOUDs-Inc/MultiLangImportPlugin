#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="on">ログ機能OnOff</param>
MultiLangTextController::MultiLangTextController(bool logOn)
{
	this->pLogger = new UnicodeLogger(logOn);

	// クラス生成時に多言語使用状態にし、他の処理の前に多言語使用可能状況を準備する
	// 他の処理の際、enable:trueを確認すること
	this->isEnable = SetProjectMLEnable();

	if (this->isEnable)
	{
		bool result;

		result = this->GetPageNames(this->pageNames);
		if (!result) {
			this->isEnable = false;
			return;
		}
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
/// プロジェクトの多言語使用可否状態の取得
/// </summary>
/// <returns></returns>
bool MultiLangTextController::IsEnabled()
{
	return this->isEnable;
}

bool MultiLangTextController::GetPageNames(std::vector<std::string>& list)
{
	BOOL mxResult;

	int pageCount;
	mxResult = MxPluginPort_Project_MultiLang_GetCount(&pageCount);
	if (!mxResult) {
		return false;
	}

	for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
	{
		char* pname = nullptr;
		
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
