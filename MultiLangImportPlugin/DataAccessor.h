#pragma once

using namespace std;

/// <summary>
/// SDK�f�[�^�A�N�Z�X�N���X
/// </summary>
class DataAccessor {

	HINSTANCE hinstDLL;
	LPVOID lpvReserved;

	string GetDirectoryFromPath(const string& filepath);

public:
	DataAccessor(HINSTANCE hinstDLL, LPVOID lpvReserved);
	~DataAccessor() = default;

	bool GetProjectInfo(SdkData& data);

	bool SetTextCastDataInMultiLanguage(WriteData& writeData, SdkData& sdkData);

};
