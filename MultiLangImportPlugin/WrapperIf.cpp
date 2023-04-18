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
	writeData.selectedLanguageIndex = DownloadInteger("DefaultLanguageIndex");
	writeData.subcastNameIndex = DownloadInteger("SubcastNameIndex");
	int textCastNameCount = DownloadInteger("TextCastNameCount");
	int languageNameCount = DownloadInteger("LanguageNameCount");

	bool flagAddIfLangPageNotFound = DownloadFlag("AddIfLangPageNotFound");
	bool flagUseSubcastName = DownloadFlag("UseSubcastName");

	// �e�L�X�g�L���X�g�����X�g��UI���牺�낷
	char** textCastNameArray = DownloadStringArray("TextCastNameArray");
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++)
	{
		std::string textCastName = std::string(textCastNameArray[castIndex]);

		// �e�L�X�g�L���X�g�����X�g�ɕێ�
		writeData.textCastNameList.push_back(textCastName);
	}

	// �e�L�X�g�L���X�g�����X�g�̃��������
	for (int castIndex = 0; castIndex < textCastNameCount; castIndex++) {
		delete[] textCastNameArray[castIndex];
	}
	delete[] textCastNameArray;



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

	for (int rowIndex = 0; rowIndex < textCastNameCount; rowIndex++) {
		TextData* textDataRow = textDataTable[rowIndex];

		for (int colIndex = 0; colIndex < languageNameCount; colIndex++) {
			TextData textData = textDataRow[colIndex];
		}
	}

	// ������C���|�[�g�f�[�^��ێ�
	// CODE HERE




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
	dataAccessor.GetProjectInfo(sdkData);

	// (char*�ɐ؂�ւ���)�v���W�F�N�g����.NET���ɓ]��
	UploadProjectInfo(sdkData.projectPath.c_str(), sdkData.projectName.c_str());

	// SDK����e�L�X�g�L���X�g�����擾���A.net���ɃA�b�v����
	dataAccessor.GetTextCastNames(sdkData);

	// vector<string>����vector<char*>�ɕϊ�
	vector<char*> namePointers;
	for (size_t idx = 0; idx < sdkData.textCastNames.size(); idx++) {
		char* pc = (char*)sdkData.textCastNames[idx].c_str();
		namePointers.push_back(pc);
	}

	// ���M�p�e�L�X�g�L���X�g���|�C���^�z��
	char** sentNamePointers = nullptr;
	// �e�L�X�g�L���X�g���̎��f�[�^�����蓖��
	if (0 < namePointers.size()) {
		sentNamePointers = &(namePointers[0]);
	}


	// UI���ɐ��������J�n���˗�
	process_result = BeginProcess();
	if (!process_result) {
		return;
	}


	// SDK�ւ̏������ݗp�f�[�^
	WriteData writeData;

	// UI�̃f�[�^��S�ĉ��낵�ď������ݗp�f�[�^�̈�Ɉړ�
	DownloadAllUIData(writeData);

	

	// �o�̓X�N���v�g�L���X�g���擾
	//char* pScriptName = DownloadString("DownloadFontColorTableScriptName");
	//writeData.scriptName = string(pScriptName);
	//delete[] pScriptName;

	// �o�̓X�N���v�g�L���X�g�R�[�h�擾
	//char* pScriptCode = DownloadString("DownloadFontColorTableScriptCode");
	//writeData.tableScriptCode = string(pScriptCode);
	//delete[] pScriptCode;

	// �o�̓X�N���v�g�L���X�g�R�[�h��SDK�ŏ�������
	//bool write_result = dataAccessor.WriteFontColorTableScript(writeData);
	bool write_result = false;
	if (!write_result) {
		MessageBox(this->hWnd, L"Writing script cast failed.", L"Error", MB_OK);
	}
	else {
		MessageBox(this->hWnd, L"Writing script cast succeeded.", L"Error", MB_OK);
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
