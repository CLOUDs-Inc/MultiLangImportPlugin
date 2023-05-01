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

	// �v���W�F�N�g�t�@�C���p�X��ێ�
	data.projectPath = string(pProjectPath);
	// �v���W�F�N�g����ێ�
	data.projectName = string(pProjectName);

	return true;
}

/// <summary>
/// �f�t�H���g����ݒ�
/// </summary>
/// <param name="writeData">�������݊Ǘ��f�[�^</param>
/// <returns>��������</returns>
bool DataAccessor::SetDefaultLanguage(WriteData& writeData)
{
	bool result = true;
	int mxResult;

	// �f�t�H���g���ꂪ�ݒ肳��Ă��Ȃ����(-1)�Atrue�ŏI��
	if (writeData.selectedLanguageIndex < 0) {
		return result;
	}

	// �f�t�H���g����C���f�b�N�X
	int defaultLangIndex = writeData.selectedLanguageIndex;
	
	// �f�t�H���g����ݒ�


	return result;
}

/// <summary>
/// �e�L�X�g�L���X�g�f�[�^��������
/// </summary>
/// <param name="writeData">�������݊Ǘ��f�[�^</param>
/// <returns>��������</returns>
bool DataAccessor::SetTextCastDataInMultiLanguage(WriteData& writeData, SdkData& sdkData)
{
	bool result = true;
	int mxResult;

	string logDir = GetDirectoryFromPath(sdkData.projectPath);
	// ���K�[���擾
	//SingleLogger* logger = SingleLogger::getLogger()
	// ���O�F����


	// ���O�F�C���|�[�gExcel�t�@�C���p�X���



	MultiLangTextController mlTextController;

	// ����y�[�W�ǉ������̗L���m�F
	if (writeData.flagAddIfLanguagePageNotFound)
	{
		// �ǉ�����̃��X�g���쐬�i�T�u�L���X�g�p�Ƃ��Ă���Excel��f�[�^���O�����߁j
		vector<string> appendPageNameList;
		for (size_t index = 0; index < writeData.languageNameList.size(); index++)
		{
			// �T�u�L���X�g���g�pOn�Ȃ�A�T�u�L���X�g�Ɏg�p������̃y�[�W���͒ǉ����Ȃ�
			if (writeData.flagUseSubcastName && writeData.subcastNameIndex == (int)index)
			{
				continue;
			}

			appendPageNameList.push_back(writeData.languageNameList[index]);
		}

		// ����y�[�W�ǉ�����
		mlTextController.SetPageNames(appendPageNameList);
		
		// ���O�F�ǉ�����


	}



	// �L���X�g���ǉ�����
	// CastNum=MxPluginPort_Cast_CreateText(CastNum,NULL);

	// ��������L���X�g������

	// �L���X�g�ǉ� or �Q��

	// �����R�[�h�w��

	// ����y�[�W�w��

	// �e�L�X�g

	// �t�H���g��

	// �t�H���g�T�C�Y

	// �t�H���g�F(RGB)

	// �t�H���g�X�^�C��










	// �L���X�g���ǉ����������܂�


	return result;
}

//bool DataAccessor::WriteFontColorTableScript(WriteData& writeData)
//{
//	bool result = true;
//	int mxResult;
//	int castNo;
//
//	// �������O�̃X�N���v�g�L���X�g�̗L�����m�F����
//	mxResult = MxPluginPort_Cast_FindCast(ct_Script, (char*)writeData.scriptName.c_str());
//	if (mxResult >= 0) {
//		// ��������
//		// �L���X�g�ԍ���ݒ�
//		castNo = mxResult;
//	}
//	else
//	{
//		// �L���X�g��������Ȃ�
//
//		// �X�N���v�g�L���X�g�́i�u�����N���܂񂾁j�����擾����
//		mxResult = MxPluginPort_Cast_GetCastCount(ct_Script);
//		if (mxResult < 0) {
//			// �L���X�g�ԍ����Ȃ�
//			result = false;
//			goto FUNC_ERROR;
//		}
//
//		// �L���X�g�ԍ��Ƃ��Ė����Ɉ�u�����N���󂯂��ԍ����w�肷��
//		castNo = mxResult + 1;
//
//		// �X�N���v�g�L���X�g�̍쐬
//		mxResult = MxPluginPort_Cast_CreateScript(castNo, (char*)writeData.scriptName.c_str());
//		if (mxResult < 0) {
//			// �L���X�g�쐬���s
//			result = false;
//			goto FUNC_ERROR;
//		}
//	}
//
//	// �R�[�h��������
//	mxResult = MxCast_Script_SetCode(castNo, (void*)writeData.tableScriptCode.c_str());
//	if (mxResult < 0) {
//		result = false;
//		goto FUNC_ERROR;
//	}
//
//
//FUNC_ERROR:
//
//	return result;
//}

