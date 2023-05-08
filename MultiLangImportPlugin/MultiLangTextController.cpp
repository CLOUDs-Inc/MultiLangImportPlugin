#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="on">���O�@�\OnOff</param>
MultiLangTextController::MultiLangTextController(WriteData& writeData)
{
	this->writeData = writeData;
	this->pLogger = new UnicodeLogger(writeData.flagLogOutput);

	std::wstring msg = L"# Import File: " + writeData.importExcelFileFullPathWide;
	this->pLogger->log(msg);

	// �N���X�������ɑ�����g�p��Ԃɂ��A���̏����̑O�ɑ�����g�p�\�󋵂���������
	// ���̏����̍ہAenable:true���m�F���邱��
	this->isEnable = SetProjectMLEnable();

	if (this->isEnable)
	{
		bool result;

		result = this->GetPageNames(this->pageNames);
		if (!result) {
			this->isEnable = false;
			return;
		}
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MultiLangTextController::~MultiLangTextController()
{
	delete this->pLogger;
}

/// <summary>
/// �v���W�F�N�g�̑�����g�p�ۏ�Ԃ̎擾
/// </summary>
/// <returns></returns>
bool MultiLangTextController::IsEnabled()
{
	return this->isEnable;
}

bool MultiLangTextController::GetPageNames(std::vector<std::string>& list)
{
	BOOL mxResult;

	int pageCount;
	mxResult = MxPluginPort_Project_MultiLang_GetCount(&pageCount);
	if (!mxResult) {
		return false;
	}

	for (int pageIndex = 0; pageIndex < pageCount; pageIndex++)
	{
		char* pname = nullptr;
		
		mxResult = MxPluginPort_Project_MultiLang_GetName(pageIndex, &pname);
		if (!mxResult) {
			return false;
		}

		std::string pageName = std::string(pname);
		list.push_back(pageName);
	}

	return true;
}

/// <summary>
/// �v���W�F�N�g�̑�����g�p��Ԃ�On�ɂ���
/// </summary>
/// <returns>On������</returns>
bool MultiLangTextController::SetProjectMLEnable()
{
	BOOL mxResult;

	BOOL isEnabled = false;
	// ���v���W�F�N�g��������g�p�\���m�F����
	mxResult = MxPluginPort_Project_MultiLang_GetEnabled(&isEnabled);

	if (!mxResult) {
		return false;
	}

	// ���ݑ����ꖢ�g�p�Ȃ�g�p�������̂ŁA
	if (!isEnabled) {
		// ��������g�p�\�ɂ���
		mxResult = MxPluginPort_Project_MultiLang_SetEnabled(true);
	}

	return mxResult;
}

/// <summary>
/// �v���W�F�N�g�Ɏg�p����������y�[�W��ǉ��ŃZ�b�g����
/// �����y�[�W�Əd������ꍇ�̓X�L�b�v�Ő����Ƃ���
/// </summary>
/// <param name="list">�ǉ��g�p����������y�[�W</param>
/// <returns>�y�[�W�ݒ�̐���</returns>
bool MultiLangTextController::SetPageNames(std::vector<std::string>& list)
{
	BOOL mxResult = false;
	std::vector<int> appendIndexList;

	// �ǉ��������y�[�W�������ɑ��݂��邩�m�F���A�Ȃ��ꍇ�A�ǉ����X�g�̃C���f�b�N�X�Ń��X�g�����
	for (size_t index = 0; index < list.size(); index++)
	{
		bool exists = std::find(this->pageNames.begin(), this->pageNames.end(), list[index]) != this->pageNames.end();
		// ���݂��Ȃ������ꍇ�A���̃C���f�b�N�X��ێ�����
		if (!exists)
		{
			appendIndexList.push_back(index);
		}
	}

	// �ێ������C���f�b�N�X�̌���y�[�W��ǉ�����
	for (size_t index = 0; index < appendIndexList.size(); index++)
	{
		int pageIndex = appendIndexList[index];
		mxResult = MxPluginPort_Project_MultiLang_Add(list[pageIndex].c_str());
		if (!mxResult) {
			return false;
		}

		std::string msg = "LANGUAGE [" + list[pageIndex] + "]: Added";
		this->pLogger->log(msg);
	}

	return true;
}



bool MultiLangTextController::SetTextProperty(int castNumber, TextData& textData) {
	bool mxResult = false;

	if (this->writeData.flagApplyFontNameToTextCast){
		mxResult = MxPluginPort_CastPropety_SetDataPtr(ct_Text, castNumber, cp_Text_FontName, (void*)textData.fontName.c_str());
		if (!mxResult) {
			return false;
		}
	}

	if (this->writeData.flagApplyFontSizeToTextCast) {
		mxResult = MxPluginPort_CastPropety_SetDataInt(ct_Text, castNumber, cp_Text_FontSize, (int)textData.fontSize);
		if (!mxResult) {
			return false;
		}
	}

	if (this->writeData.flagApplyTextColorToTextCast) {
		int colorValue = (textData.colorR & 0x000000ff)
			+ ((textData.colorG << 8) & 0x0000ff00)
			+ ((textData.colorB << 16) & 0x00ff0000);
		mxResult = MxPluginPort_CastPropety_SetDataInt(ct_Text, castNumber, cp_Text_FontColor, colorValue);
		if (!mxResult) {
			return false;
		}
	}

	if (this->writeData.flagApplyStringToTextCast) {
		bool isUnicodeTextCast = true;
		if (isUnicodeTextCast) {
			mxResult = MxPluginPort_CastPropety_SetDataPtr(ct_Text, castNumber, cp_Text_TextData, (void*)textData.wtext.c_str());
		}
		else {
			mxResult = MxPluginPort_CastPropety_SetDataPtr(ct_Text, castNumber, cp_Text_TextData, (void*)textData.text.c_str());
		}
		if (!mxResult) {
			return false;
		}
	}

	return true;
}
