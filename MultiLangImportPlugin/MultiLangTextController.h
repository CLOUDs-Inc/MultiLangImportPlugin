#pragma once

#include "pch.h"

class MultiLangTextController
{
private:
	bool isEnable;

	WriteData writeData;

	std::vector<std::string> pageNames;
	UnicodeLogger* pLogger = nullptr;

	bool GetPageNames(std::vector<std::string>& list);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MultiLangTextController(WriteData& writeData);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MultiLangTextController();

	bool IsEnabled();
	bool SetProjectMLEnable();
	bool SetPageNames(std::vector<std::string>& list);

	bool SetTextProperty(int castNumber, TextData& textData);

};
