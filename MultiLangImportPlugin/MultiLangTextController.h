#pragma once

#include "pch.h"

class MultiLangTextController
{
private:
	bool isEnable;

	WriteData writeData;

	std::vector<std::string> pageNames;
	std::string firstPageName;
	int columnIndexOfFirstPageName;

	UnicodeLogger* pLogger = nullptr;

	int  GetNewTextCastNumber();
	bool GetPageNames(std::vector<std::string>& list);
	int  GetPageNumber(std::string pageName);
	bool AddPageNames();
	bool ImportTextDataTable();

	bool UpdateTextCast(std::string& castname, std::vector<TextData>& textDataRow);

	bool ImportTextDataRow(std::string& castname, std::vector<TextData>& textDataRow);
	bool ImportTextDataAsNewCast(std::string& castname, std::vector<TextData>& textDataRow);
	bool SetTextDataCellToTextCast(int castNumber, int colIndex, TextData& textData, TextData& inheritPropData, bool isFirstPropInherit, bool isUTF);
	bool CreateLangPageToTextCast(int castNumber, int pageNumber, bool& createPageFlag);
	bool SetTextProperty(int castNumber, int pageNumber, TextData& textData, TextData& inheritPropData, bool isFirstPropInherit, bool createPageFlag, bool isUTF);


	bool CheckTextDataRowMustBeUTF(std::vector<TextData>& textDataRow);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MultiLangTextController(WriteData& writeData);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MultiLangTextController();

	bool ImportTextData();

	bool IsEnabled();
	bool SetDefaultLanguage(WriteData& writeData);
	bool SetProjectMLEnable();
	bool SetPageNames(std::vector<std::string>& list);



	string GetFirstPageName();


	int FindTextCastNumber(std::string& castname);


	void TestWriteTextCast();
};
