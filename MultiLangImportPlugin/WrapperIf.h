#pragma once
#include "pch.h"

#define PROC_ATTACH(pfunc, functype, hmodule, result, label) \
    pfunc = (functype)GetProcAddress(hmodule, #pfunc); \
    if (pfunc == nullptr) { \
		DWORD errorCode = GetLastError(); \
		result = false; \
        goto label;\
	}

#define DELETE_CODE_INFO(pInfo) \
	delete[] (pInfo)->code; \
	delete[] (pInfo)->name; \
	delete pInfo;

#define DELETE_TEXT_DATA(pData) \
	delete[] (pData)->text; \
	delete[] (pData)->fontName; \
	delete pData;


typedef bool(*PProcCreateWrapper)();
typedef bool(*PProcBeginProcess)();

typedef void(*PProcUploadProjectInfo)(const char* filepath, const char* projectName);
typedef void(*PProcUploadTextCastNames)(int names_len, char** names);

typedef TextData** (*PProcDownloadTextDataTable)();
typedef char** (*PProcDownloadStringArray)(const std::string& ArrayName);
typedef char* (*PProcDownloadString)(const std::string& methodName);
typedef int(*PProcDownloadInteger)(const std::string& variableName);
typedef float(*PProcDownloadFloat)(const std::string& variableName);
typedef bool(*PProcDownloadFlag)(const std::string& flagName);


using namespace std;

/// <summary>
/// Wrapper DLLとのIF
/// </summary>
class WrapperIf {

	// function pointer
	PProcCreateWrapper CreateWrapper = nullptr;
	PProcBeginProcess BeginProcess = nullptr;

	PProcUploadProjectInfo UploadProjectInfo = nullptr;

	PProcDownloadTextDataTable DownloadTextDataTable = nullptr;
	PProcDownloadStringArray DownloadStringArray = nullptr;
	PProcDownloadString DownloadString = nullptr;
	PProcDownloadInteger DownloadInteger = nullptr;
	PProcDownloadFloat DownloadFloat = nullptr;
	PProcDownloadFlag DownloadFlag = nullptr;

	HWND hWnd;
	HINSTANCE hinstDLL;
	LPVOID lpvReserved;

	// SDKからの必要データ
	SdkData sdkData;

	HMODULE hModule = 0;

	void DownloadAllUIData(WriteData& writeData);

public:
	WrapperIf(HWND hWnd, HINSTANCE hinstDLL, LPVOID lpvReserved);
	~WrapperIf() = default;

	bool init();
	void execute();
	void cleanUp();
};
