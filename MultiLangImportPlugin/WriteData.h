#pragma once

using namespace std;

class WriteData
{
public:
	/// <summary>
	/// デフォルト言語インデックス
	/// </summary>
	int selectedLanguageIndex;

	/// <summary>
	/// 言語名リスト
	/// </summary>
	vector<string> languageNameList;

	/// <summary>
	/// サブキャスト名指定インデックス
	/// </summary>
	int subcastNameIndex;

	/// <summary>
	/// テキストキャスト名リスト
	/// </summary>
	vector<string> textCastNameList;


	// サブキャスト設定 ==========================
	bool flagUseSubcastName;
	bool flagUseSubcastNameWhenSearchingForCast;
	bool flagAddSubcastNameWhenCreatingANewCast;
	bool flagUseUnderscoreForConjunctionInSubcastName;
	string conjunctionString;
	int subcastIndex;
};
