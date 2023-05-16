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

	int GetNewTextCastNumber();
	int FindTextCastNumber(std::string& castname);
	string GetTextCastNameOfProject(int castNumber);

	bool GetPageNames(std::vector<std::string>& list);
	int  GetPageNumber(std::string pageName);
	bool AddPageNames();
	bool ImportTextDataTable();

	bool UpdateTextCastLangPage(int castNumber, TextData& textData, std::string& langPageName, bool isUnicode, int cloneIndex);
	bool UpdateTextCast(std::string& castname, std::vector<TextData>& textDataRow);

	bool ImportTextDataRow2(int rowIndex, std::vector<TextData>& textDataRow);
	bool CreateNewTextCast(int castnumber, std::string& castname, bool isUnicode);
	bool CloneTextCast(int toCastNumber, int fromCastNumber);
	void CloneTextCastPage(int toCastNumber, int toLangPage, int fromCastNumber, int fromLangPage, bool enableFontName, bool enableFontSize, bool enableFontColor);

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




	void TestWriteTextCast();
};
