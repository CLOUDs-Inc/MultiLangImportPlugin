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
	/// テキストキャスト名リスト
	/// </summary>
	vector<string> textCastNameList;


	vector<vector<TextData>> textDataTable;

	// Apply languages and casts設定 =============
	bool flagAddIfLanguagePageNotFound;
	bool flagAddIfTextCastNotFound;
	bool flagCreateAsUnicodeTextCast;
	bool flagNotUpdateExistingTextCast;
	bool flagInheritPropertiesOfTheFirstLangPage;
	bool flagInheritOnlyNewLangPage;

	// Apply properties設定 ======================
	bool flagApplyFontNameToTextCast;
	bool flagApplyFontSizeToTextCast;
	bool flagApplyTextColorToTextCast;
	bool flagApplyStringToTextCast;

	// サブキャスト設定 ==========================
	bool flagUseSubcastName;
	bool flagUseSubcastNameWhenSearchingForCast;
	bool flagAddSubcastNameWhenCreatingANewCast;
	bool flagUseUnderscoreForConjunctionInSubcastName;
	string conjunctionString;
	/// <summary>
	/// サブキャスト名指定インデックス
	/// </summary>
	int subcastNameIndex;

};
