#pragma once

using namespace std;

/// <summary>
/// SDKデータアクセスクラス
/// </summary>
class DataAccessor {

	HINSTANCE hinstDLL;
	LPVOID lpvReserved;

	string GetDirectoryFromPath(const string& filepath);

public:
	DataAccessor(HINSTANCE hinstDLL, LPVOID lpvReserved);
	~DataAccessor() = default;

	bool GetProjectInfo(SdkData& data);

	bool SetDefaultLanguage(WriteData& writeData);
	bool SetTextCastDataInMultiLanguage(WriteData& writeData, SdkData& sdkData);
};
