#pragma once

using namespace std;

class SdkData {
public:
	string projectPath;
	wstring projectPathW;
	string projectName;

	bool multiLangEnabled;
	int langPageNumber;

	vector<string> textCastNames;
	int textCastCount{ -1 };

};
