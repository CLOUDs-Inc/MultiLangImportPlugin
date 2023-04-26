#include "pch.h"

SingleLogger* SingleLogger::instance = nullptr;

/// <summary>
/// �V���O���g�����K�[�F�R���X�g���N�^
/// </summary>
SingleLogger::SingleLogger(const std::string& filepath) {
	logFile.open(filepath, std::ios::app);
	this->openFlag = logFile.is_open();
}

/// <summary>
/// �V���O���g�����K�[�F�f�X�g���N�^
/// </summary>
SingleLogger::~SingleLogger() {
	if (logFile.is_open()) {
		logFile.close();
	}
	delete instance;
	instance = nullptr;
}

/// <summary>
/// ���K�[�C���X�^���X�擾
/// </summary>
/// <returns>���K�[�C���X�^���X</returns>
SingleLogger* SingleLogger::getLogger(const std::string& filepath) {
	if (instance == nullptr) {
		instance = new SingleLogger(filepath);
	}
	return instance;
}

void SingleLogger::log(const std::string& message) {
	if (this->openFlag) {
		logFile << message << std::endl;
	}
}
