#pragma once

#include "pch.h"

class MultiLangTextController
{
private:
	bool isEnable;

	WriteData writeData;

	std::string firstPageName;
	int columnIndexOfFirstPageName;

	UnicodeLogger* pLogger = nullptr;

	int GetNewTextCastNumber();
	int FindTextCastNumber(std::string& castname);
	string GetTextCastNameOfProject(int castNumber);

	bool GetPageNames(std::vector<std::string>& list);
	int GetProjectLangNumber(std::string pageName);
	bool AddPageNames(std::vector<std::string>& list);
	bool ImportTextDataTable();

	bool UpdateTextCastLangPage(int castNumber, TextData& textData, std::string& langPageName, bool isUnicode, int cloneIndex, bool addedCastFlag);

	bool ImportTextDataRow(int rowIndex, std::vector<TextData>& textDataRow);
	bool CreateNewTextCast(int castnumber, std::string& castname, bool isUnicode);
	bool CloneTextCast(int toCastNumber, int fromCastNumber);
	void CloneTextCastPage(int toCastNumber, int toLangPage, int fromCastNumber, int fromLangPage, bool enableFontName, bool enableFontSize, bool enableFontColor);

	bool SetTextDataCellToTextCast(int castNumber, int colIndex, TextData& textData, TextData& inheritPropData, bool isFirstPropInherit, bool isUTF);
	bool CreateLangPageToTextCast(int castNumber, int pageNumber, bool addedCastFlag, bool& createPageFlag);


	bool CheckTextDataRowMustBeUTF(std::vector<TextData>& textDataRow);

	double color_lum(int c);
	int ChooseBackColor(int color);

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

	bool SetProjectMLEnable();



	string GetFirstPageName();




	void TestWriteTextCast();
};
