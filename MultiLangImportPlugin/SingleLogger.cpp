#include "pch.h"

SingleLogger* SingleLogger::instance = nullptr;

/// <summary>
/// シングルトンロガー：コンストラクタ
/// </summary>
SingleLogger::SingleLogger(const std::string& filepath) {
	logFile.open(filepath, std::ios::app);
	this->openFlag = logFile.is_open();
}

/// <summary>
/// シングルトンロガー：デストラクタ
/// </summary>
SingleLogger::~SingleLogger() {
	if (logFile.is_open()) {
		logFile.close();
	}
	delete instance;
	instance = nullptr;
}

/// <summary>
/// ロガーインスタンス取得
/// </summary>
/// <returns>ロガーインスタンス</returns>
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
