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
	/// �T�u�L���X�g���w��C���f�b�N�X
	/// </summary>
	int subcastNameIndex;

	/// <summary>
	/// �e�L�X�g�L���X�g�����X�g
	/// </summary>
	vector<string> textCastNameList;


	// �T�u�L���X�g�ݒ� ==========================
	bool flagUseSubcastName;
	bool flagUseSubcastNameWhenSearchingForCast;
	bool flagAddSubcastNameWhenCreatingANewCast;
	bool flagUseUnderscoreForConjunctionInSubcastName;
	string conjunctionString;
	int subcastIndex;
};
