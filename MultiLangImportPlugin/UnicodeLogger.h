#pragma once
#include "pch.h"

class UnicodeLogger {

	std::ofstream logFile;
	bool openFlag;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::string getTempDirectory();
	std::string getLogFilename();

public:
	UnicodeLogger(bool on);
	~UnicodeLogger();
	std::string getLogFileFullPath();

	void log(const std::string& message);
	void log(const std::wstring& message);

};
