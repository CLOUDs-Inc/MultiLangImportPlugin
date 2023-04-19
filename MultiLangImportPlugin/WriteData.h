#pragma once

using namespace std;

class WriteData
{
public:
	/// <summary>
	/// �f�t�H���g����C���f�b�N�X
	/// </summary>
	int selectedLanguageIndex;

	/// <summary>
	/// ���ꖼ���X�g
	/// </summary>
	vector<string> languageNameList;

	/// <summary>
	/// �e�L�X�g�L���X�g�����X�g
	/// </summary>
	vector<string> textCastNameList;


	vector<vector<TextData>> textDataTable;

	// Apply languages and casts�ݒ� =============
	bool flagAddIfLanguagePageNotFound;
	bool flagAddIfTextCastNotFound;
	bool flagCreateAsUnicodeTextCast;
	bool flagNotUpdateExistingTextCast;
	bool flagInheritPropertiesOfTheFirstLangPage;
	bool flagInheritOnlyNewLangPage;

	// Apply properties�ݒ� ======================
	bool flagApplyFontNameToTextCast;
	bool flagApplyFontSizeToTextCast;
	bool flagApplyTextColorToTextCast;
	bool flagApplyStringToTextCast;

	// �T�u�L���X�g�ݒ� ==========================
	bool flagUseSubcastName;
	bool flagUseSubcastNameWhenSearchingForCast;
	bool flagAddSubcastNameWhenCreatingANewCast;
	bool flagUseUnderscoreForConjunctionInSubcastName;
	string conjunctionString;
	/// <summary>
	/// �T�u�L���X�g���w��C���f�b�N�X
	/// </summary>
	int subcastNameIndex;

};
