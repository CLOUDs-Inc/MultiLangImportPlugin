#include "pch.h"

//--------------------
// Wrapper DLL�Ƃ�IF
//--------------------
WrapperIf::WrapperIf(HWND hWnd, HINSTANCE hinstDLL, LPVOID lpvReserved)
{
	this->hWnd = hWnd;
	this->hinstDLL = hinstDLL;
	this->lpvReserved = lpvReserved;
}

/// <summary>
/// UI����̃f�[�^�����o�������܂Ƃ�
/// </summary>
/// <param name="writeData">�������ݗp�f�[�^�ێ��̈�</param>
void WrapperIf::DownloadAllUIData(WriteData& writeData)
{
	// �f�t�H���g���ꖼ��
	char* pDefaultLangName = DownloadString("DownloadDefaultLanguageName");
	writeData.defaultLanguageName = std::string(pDefaultLangName);
	delete[] pDefaultLangName;
	// �T�u�L���X�g������C���f�b�N�X
	writeData.subcastNameIndex = DownloadInteger("SubcastNameIndex");

	// �C���|�[�gExcel�t�@�C���t���p�X������
	char* pExcelFullPathStr = DownloadString("DownloadImportExcelFilePath");
	writeData.importExcelFileFullPath = std::string(pExcelFullPathStr);
	delete[] pExcelFullPathStr;
	// �C���|�[�gExcel�t�@�C���t���p�X������i���C�h�j
	wchar_t* pExcelFullPathWStr = DownloadWString("DownloadImportExcelFilePath");
	writeData.importExcelFileFullPathWide = std::wstring(pExcelFullPathWStr);
	delete[] pExcelFullPathWStr;

	// Apply languages and casts�ݒ� =============
	writeData.flagAddIfLanguagePageNotFound = DownloadFlag("AddIfLangPageNotFound");
	writeData.flagAddIfTextCastNotFound = DownloadFlag("AddIfTextCastNotFound");
	writeData.flagCreateAsUnicodeTextCast = DownloadFlag("CreateAsUnicodeTextCast");
	writeData.flagNotUpdateExistingTextCast = DownloadFlag("NotUpdateExistingTextCast");
	writeData.flagInheritPropertiesOfTheFirstLangPage = DownloadFlag("InheritPropertiesOfTheFirstLangPage");
	writeData.flagInheritOnlyNewLangPage = DownloadFlag("InheritOnlyNewLangPage");

	// Apply properties�ݒ� ======================
	writeData.flagApplyFontNameToTextCast = DownloadFlag("ApplyFontName");
	writeData.flagApplyFontSizeToTextCast = DownloadFlag("ApplyFontSize");
	writeData.flagApplyTextColorToTextCast = DownloadFlag("ApplyTextColor");
	writeData.flagApplyStringToTextCast = DownloadFlag("ApplyString");

	// ���M���O�ݒ� ==============================
	writeData.flagLogOutput = DownloadFlag("LogOutput");

	// �T�u�L���X�g�ݒ� ==========================
	writeData.flagUseSubcastName = DownloadFlag("UseSubcastName");
	writeData.flagUseSubcastNameWhenSearchingForCast = DownloadFlag("UseSubcastNameWhenSearchingForCast");
	writeData.flagAddSubcastNameWhenCreatingANewCast = DownloadFlag("AddSubcastNameWhenCreatingANewCast");
	writeData.flagUseUnderscoreForConjunctionInSubcastName = DownloadFlag("FlagUseUnderscoreForConjunctionInSubcastName");
	char* pConjunctionStr = DownloadString("DownloadSubcastConjunctionString");
	writeData.conjunctionString = std::string(pConjunctionStr);
	delete[] pConjunctionStr;

	int textCastNameCount = DownloadInteger("TextCastNameCount");
	int languageNameCount = DownloadInteger("LanguageNameCount");

	// �e�L�X�g�L���X�g�����X�g�i�T�u�L���X�g���H�Ȃ��j��UI���牺�낷
	char** textCastNameArrayLoneMod = DownloadStringArray("TextCastNameArrayLoneMod");
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++)
	{
		std::string textCastName = std::string(textCastNameArrayLoneMod[castIndex]);

		// �e�L�X�g�L���X�g�����X�g�ɕێ�
		writeData.textCastNameListLoneMod.push_back(textCastName);
	}

	// �e�L�X�g�L���X�g�����X�g�̃��������
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++) {
		delete[] textCastNameArrayLoneMod[castIndex];
	}
	delete[] textCastNameArrayLoneMod;


	// �T�u�L���X�g���������X�g��UI���牺�낷
	char** subPartNameArrayMod = DownloadStringArray("SubPartNameArrayMod");
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++)
	{
		std::string textCastName = std::string(subPartNameArrayMod[castIndex]);

		// �e�L�X�g�L���X�g�����X�g�ɕێ�
		writeData.subPartNameListMod.push_back(textCastName);
	}

	// �e�L�X�g�L���X�g�����X�g�̃��������
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++) {
		delete[] subPartNameArrayMod[castIndex];
	}
	delete[] subPartNameArrayMod;


	// �e�L�X�g�L���X�g�����X�g�i�T�u�L���X�g���H�ς݁j��UI���牺�낷
	char** textCastNameArrayConjMod = DownloadStringArray("TextCastNameArrayConjMod");
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++)
	{
		std::string textCastName = std::string(textCastNameArrayConjMod[castIndex]);

		// �e�L�X�g�L���X�g�����X�g�ɕێ�
		writeData.textCastNameListConjMod.push_back(textCastName);
	}

	// �e�L�X�g�L���X�g�����X�g�̃��������
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++) {
		delete[] textCastNameArrayConjMod[castIndex];
	}
	delete[] textCastNameArrayConjMod;



	// ���ꖼ���X�g��UI���牺�낷
	char** languageNameArray = DownloadStringArray("LanguageNameArray");
	for (int langIndex = 0; langIndex < languageNameCount; langIndex++)
	{
		std::string languageName = std::string(languageNameArray[langIndex]);

		// ���ꖼ���X�g�ɕێ�
		writeData.languageNameList.push_back(languageName);
	}

	// ���ꖼ���X�g�̃��������
	for (int langIndex = 0; langIndex < languageNameCount; langIndex++) {
		delete[] languageNameArray[langIndex];
	}
	delete[] languageNameArray;



	// ������C���|�[�g�e�L�X�g�f�[�^��UI���牺�낷
	TextData** textDataTable = DownloadTextDataTable();

	// ������C���|�[�g�f�[�^��ێ�
	for (int rowIndex = 0; rowIndex < textCastNameCount; rowIndex++) {
		TextData* textDataRow = textDataTable[rowIndex];

		vector<TextData> textDataRowVector;
		for (int colIndex = 0; colIndex < languageNameCount; colIndex++) {
			TextData textData = textDataRow[colIndex];
			textDataRowVector.push_back(textData);
		}
		writeData.textDataTable.push_back(textDataRowVector);
	}

	// ������C���|�[�g�e�L�X�g�f�[�^�̃��������
	for (int rowIndex = 0; rowIndex < textCastNameCount; rowIndex++)
	{
		// ��s�����
		delete[] textDataTable[rowIndex];
	}
	// �e�[�u���S�̂����
	delete[] textDataTable;
}



/// <summary>
/// ����������
/// </summary>
/// <returns>����</returns>
bool WrapperIf::init()
{
	bool result = true;

	// wrapper.dll�̃��[�h LoadLibrary
	// -------------------------------
	wchar_t ModulePath[MAX_PATH + 1];
	GetModuleFileName(hinstDLL, ModulePath, MAX_PATH);

	wchar_t* slash_pos = wcsrchr(ModulePath, '\\');
	*slash_pos = 0;

	// Plug-in DLL�̃t�@�C���p�X�����b�p�[DLL�ɕϊ�
	wcscat_s(ModulePath, MAX_PATH, MANAGED_WRAPPER_DLL);

	// ModulePath�`�F�b�N
	size_t pathSize = wcslen(ModulePath) + 1;
	size_t convertedChars = 0;
	char* pathStr = new char[pathSize * 2];
	wcstombs_s(&convertedChars, pathStr, pathSize * 2, ModulePath, _TRUNCATE);
	delete[] pathStr;

	// DLL�t�@�C���̃��[�h
	hModule = LoadLibrary(ModulePath);
	if (hModule == NULL) {
		MessageBox(this->hWnd, L"Wrapper DLL read failed.", L"Error", MB_OK);
		result = false;
		goto INIT_ERROR;
	}

	// DLL�̊֐��A�^�b�`
	PROC_ATTACH(CreateWrapper, PProcCreateWrapper, hModule, result, INIT_ERROR);
	PROC_ATTACH(BeginProcess, PProcBeginProcess, hModule, result, INIT_ERROR);

	PROC_ATTACH(UploadProjectInfo, PProcUploadProjectInfo, hModule, result, INIT_ERROR);

	PROC_ATTACH(DownloadTextDataTable, PProcDownloadTextDataTable, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadStringArray, PProcDownloadStringArray, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadString, PProcDownloadString, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadWString, PProcDownloadWString, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadInteger, PProcDownloadInteger, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadFloat, PProcDownloadFloat, hModule, result, INIT_ERROR);
	PROC_ATTACH(DownloadFlag, PProcDownloadFlag, hModule, result, INIT_ERROR);

INIT_ERROR:

	return result;
}

/// <summary>
/// ���������c�[���������s
/// </summary>
void WrapperIf::execute()
{
	BOOL result = TRUE;

	bool create_wrapper_result = false;
	bool process_result = false;

	// CreateWrapper
	create_wrapper_result = CreateWrapper();
	if (!create_wrapper_result) {
		MessageBox(this->hWnd, L"GUI DLL read failed.", L"Error", MB_OK);
		return;
	}

	// SDK�A�N�Z�X�I�u�W�F�N�g
	DataAccessor dataAccessor(hinstDLL, lpvReserved);

	// SDK����v���W�F�N�g�����擾���A.net���ɃA�b�v����
	process_result = dataAccessor.GetProjectInfo(sdkData);
	if (!process_result) {
		return;
	}

	// (char*�ɐ؂�ւ���)�v���W�F�N�g����.NET���ɓ]��
	UploadProjectInfo(sdkData.projectPath.c_str(), sdkData.projectName.c_str(), sdkData.multiLangEnabled, sdkData.langPageNumber);


	// UI���ɐ��������J�n���˗�
	process_result = BeginProcess();
	if (!process_result) {
		return;
	}


	// SDK�ւ̏������ݗp�f�[�^
	WriteData writeData;

	// UI�̃f�[�^��S�ĉ��낵�ď������ݗp�f�[�^�̈�Ɉړ�
	DownloadAllUIData(writeData);

	// ������e�L�X�g�L���X�g�f�[�^��SDK�ŏ�������
	bool write_result = dataAccessor.SetTextCastDataInMultiLanguage(writeData, sdkData);
	//bool write_result = true;
	if (write_result) {
		MessageBox(this->hWnd, L"Multi-language text casts import succeeded.", L"Error", MB_OK);
	}
	else {
		MessageBox(this->hWnd, L"Multi-language text casts import failed.", L"Error", MB_OK);
	}

	return;
}


/// <summary>
/// Wrapper IF�N���[�Y����
/// </summary>
void WrapperIf::cleanUp() {

	// dll�̃A�����[�h FreeLibrary
	if (hModule != NULL)
		FreeLibrary(hModule);

	return;
}
