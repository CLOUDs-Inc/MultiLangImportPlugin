#pragma once
#include "pch.h"

class UnicodeLogger {

	std::ofstream logFile;
	std::string filepath;
	bool openFlag;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::string getTempDirectory();
	std::string getLogFilename();
	std::string getLogFileFullPath();

public:
	UnicodeLogger(bool on);
	~UnicodeLogger();
	std::wstring getLogFileFullPathWide();
	std::string getLogDateString();

	void log(const std::string& message);
	void log(const std::wstring& message);

};
