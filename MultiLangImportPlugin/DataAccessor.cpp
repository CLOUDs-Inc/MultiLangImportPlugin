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
/// SDK�̃v���W�F�N�g���̎擾�E�i�[
/// </summary>
/// <param name="aatData">�f�[�^�Ǘ��I�u�W�F�N�g</param>
/// <returns>��������</returns>
bool DataAccessor::GetProjectInfo(SdkData& data)
{
	// �v���W�F�N�g�t�@�C���p�X���擾
	char* pProjectPath;
	pProjectPath = MxPluginPort_Project_GetContentsPath();
	if (pProjectPath == NULL) {
		return false;
	}

	// �v���W�F�N�g�����擾
	char* pProjectName;
	pProjectName = MxPluginPort_Project_GetContentsName();
	if (pProjectName == NULL) {
		return false;
	}

	// ������g�p�ݒ���v���W�F�N�g����擾
	BOOL enabled;
	BOOL mxResult = MxPluginPort_Project_MultiLang_GetEnabled(&enabled);
	if (!mxResult) {
		return false;
	}

	// ������g�p�y�[�W�����v���W�F�N�g����擾
	int pageNumber = 0;
	mxResult = MxPluginPort_Project_MultiLang_GetCount(&pageNumber);
	if (!mxResult) {
		return false;
	}

	// �v���W�F�N�g�t�@�C���p�X��ێ�
	data.projectPath = string(pProjectPath);
	// �v���W�F�N�g����ێ�
	data.projectName = string(pProjectName);
	// ������g�p��Ԃ�ێ�
	data.multiLangEnabled = enabled ? true : false;
	// ������g�p�y�[�W����ێ�
	data.langPageNumber = pageNumber;

	return true;
}

/// <summary>
/// �e�L�X�g�L���X�g�f�[�^��������
/// </summary>
/// <param name="writeData">�������݊Ǘ��f�[�^</param>
/// <returns>��������</returns>
bool DataAccessor::SetTextCastDataInMultiLanguage(WriteData& writeData, SdkData& sdkData)
{
	bool result = true;

	string logDir = GetDirectoryFromPath(sdkData.projectPath);


	MultiLangTextController mlTextController(writeData);
	result = mlTextController.ImportTextData();
	return result;
}
