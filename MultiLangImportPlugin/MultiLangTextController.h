#pragma once

#include "pch.h"

class MultiLangTextController
{
private:
	bool isEnable;

	std::vector<std::string> pageNames;


	bool GetPageNames(std::vector<std::string>& list);

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MultiLangTextController();


	bool IsEnabled();
	bool SetProjectMLEnable();
	bool SetPageNames(std::vector<std::string>& list);
};