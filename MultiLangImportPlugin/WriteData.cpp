#include "pch.h"

/// <summary>
/// UI側言語リストの中の指定の言語名のインデクスを取得
/// </summary>
/// <param name="pageName">検索言語名</param>
/// <returns>インデクス（失敗時-1）</returns>
int WriteData::getColumnIndexOfPageName(string pageName)
{
	int result = -1;

	// UI側言語リストからページ名を検索するイテレータを取得
	auto iter = std::find(this->languageNameList.begin(), this->languageNameList.end(), pageName);
	if (iter == this->languageNameList.end()) {
		// 見つからない場合-1
		return result;
	}

	// 距離（インデクス）を取得
	result = std::distance(this->languageNameList.begin(), iter);

	// サブキャスト指定列は言語名ではないとみなすので-1
	if (result == this->subcastNameIndex) {
		result = -1;
	}

	return result;
}

