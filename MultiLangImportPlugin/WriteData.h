#pragma once

using namespace std;

class WriteData
{
public:
	/// <summary>
	/// デフォルト言語名
	/// </summary>
	string defaultLanguageName;

	/// <summary>
	/// 言語名リスト
	/// </summary>
	vector<string> languageNameList;

	/// <summary>
	/// テキストキャスト名リスト（サブキャスト加工なし）
	/// </summary>
	vector<string> textCastNameListLoneMod;

	/// <summary>
	/// サブキャスト部分名リスト
	/// </summary>
	vector<string> subPartNameListMod;

	/// <summary>
	/// テキストキャスト名リスト（サブキャスト加工済み）
	/// </summary>
	vector<string> textCastNameListConjMod;

	string importExcelFileFullPath;
	wstring importExcelFileFullPathWide;

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

	// ロギング設定 ==============================
	bool flagLogOutput;

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


	// 関数 ======================================
	int getColumnIndexOfPageName(string pageName);
};
