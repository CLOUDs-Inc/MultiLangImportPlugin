#pragma once

using namespace std;

class SdkData {
public:
	string projectPath;
	wstring projectPathW;
	string projectName;

	vector<string> textCastNames;
	int textCastCount{ -1 };

};
