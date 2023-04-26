#pragma once
#include <iostream>
#include <fstream>
#include <string>

class SingleLogger {
private:
	static SingleLogger* instance;
	std::ofstream logFile;
	bool openFlag;
	SingleLogger(const std::string& filepath);

public:
	~SingleLogger();
	static SingleLogger* getLogger(const std::string& filepath);
	void log(const std::string& message);
};
