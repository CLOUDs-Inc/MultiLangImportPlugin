#pragma once

#include "pch.h"

class MultiLangTextController
{
private:
	bool isEnable;

	std::vector<std::string> pageNames;
	UnicodeLogger* pLogger = nullptr;

	bool GetPageNames(std::vector<std::string>& list);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MultiLangTextController(bool logFlag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MultiLangTextController();

	bool IsEnabled();
	bool SetProjectMLEnable();
	bool SetPageNames(std::vector<std::string>& list);
};
