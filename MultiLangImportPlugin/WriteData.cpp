#include "pch.h"

/// <summary>
/// UI�����ꃊ�X�g�̒��̎w��̌��ꖼ�̃C���f�N�X���擾
/// </summary>
/// <param name="pageName">�������ꖼ</param>
/// <returns>�C���f�N�X�i���s��-1�j</returns>
int WriteData::getColumnIndexOfPageName(string pageName)
{
	int result = -1;

	// UI�����ꃊ�X�g����y�[�W������������C�e���[�^���擾
	auto iter = std::find(this->languageNameList.begin(), this->languageNameList.end(), pageName);
	if (iter == this->languageNameList.end()) {
		// ������Ȃ��ꍇ-1
		return result;
	}

	// �����i�C���f�N�X�j���擾
	result = std::distance(this->languageNameList.begin(), iter);

	// �T�u�L���X�g�w���͌��ꖼ�ł͂Ȃ��Ƃ݂Ȃ��̂�-1
	if (result == this->subcastNameIndex) {
		result = -1;
	}

	return result;
}

