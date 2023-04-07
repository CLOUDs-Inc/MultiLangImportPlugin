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


typedef bool(*PProcCreateWrapper)();
typedef bool(*PProcBeginProcess)();

typedef void(*PProcUploadProjectInfo)(const char* filepath, const char* projectName);
typedef void(*PProcUploadTextCastNames)(int names_len, char** names);

typedef char* (*PProcDownloadString)(const std::string& methodName);


using namespace std;

/// <summary>
/// Wrapper DLLとのIF
/// </summary>
class WrapperIf {

	// function pointer
	PProcCreateWrapper CreateWrapper = nullptr;
	PProcBeginProcess BeginProcess = nullptr;

	PProcUploadProjectInfo UploadProjectInfo = nullptr;

	PProcDownloadString DownloadString = nullptr;

	HWND hWnd;
	HINSTANCE hinstDLL;
	LPVOID lpvReserved;

	// SDKからの必要データ
	SdkData sdkData;

	HMODULE hModule = 0;


public:
	WrapperIf(HWND hWnd, HINSTANCE hinstDLL, LPVOID lpvReserved);
	~WrapperIf() = default;

	bool init();
	void execute();
	void cleanUp();
};
