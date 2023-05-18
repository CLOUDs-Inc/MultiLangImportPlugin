#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
UnicodeLogger::UnicodeLogger(bool on) {
	if (on) {
		filepath = getLogFileFullPath();
		logFile.open(filepath, std::ios::app);
	}
	this->openFlag = logFile.is_open();
}

/// <summary>
/// デストラクタ
/// </summary>
UnicodeLogger::~UnicodeLogger() {
	if (logFile.is_open()) {
		logFile.close();
		this->openFlag = false;

		// ログファイルを表示する
		system(filepath.c_str());
	}
}

void UnicodeLogger::log(const std::string& msg)
{
	if (!this->openFlag) return;

	// ANSI -> wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, msg.c_str(), -1, (wchar_t*)NULL, 0);

	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// ANSI -> wstring
	MultiByteToWideChar(CP_ACP, 0, msg.c_str(), -1, cpUCS2, iBufferSize);

	// stringの生成
	std::wstring wstr(cpUCS2, cpUCS2 + iBufferSize - 1);

	delete[] cpUCS2;

	logFile << converter.to_bytes(wstr) << std::endl;
}

void UnicodeLogger::log(const std::wstring& wmsg)
{
	if (!this->openFlag) return;

	logFile << converter.to_bytes(wmsg) << std::endl;
}

std::string UnicodeLogger::getTempDirectory()
{
	const char* tempDirectory = std::getenv("TMPDIR");
	if (tempDirectory == nullptr) {
		tempDirectory = std::getenv("TMP");
		if (tempDirectory == nullptr) {
			tempDirectory = std::getenv("TEMP");
			if (tempDirectory == nullptr) {
				return std::string();
			}
		}
	}

	std::string dirname = std::string(tempDirectory) + "\\";

	return dirname;
}


std::string UnicodeLogger::getLogFilename()
{
	std::time_t now = std::time(nullptr);
	char buf[80];
	std::strftime(buf, sizeof(buf), "MLTImportLog_%Y%m%d%H%M%S.log", std::localtime(&now));

	return std::string(buf);
}


std::string UnicodeLogger::getLogFileFullPath()
{
	std::string dirname = getTempDirectory();
	std::string filename = getLogFilename();

	return dirname + filename;
}


std::string UnicodeLogger::getLogDateString()
{
	std::time_t now = std::time(nullptr);
	char buf[40];
	std::strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", std::localtime(&now));
	return std::string(buf);
}
