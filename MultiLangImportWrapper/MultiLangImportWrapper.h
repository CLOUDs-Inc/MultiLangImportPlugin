#pragma once
#pragma unmanaged
#include <vector>
#include <memory>
#include <string>
#include"../MultiLangImportPlugin/TextData.h"

#ifdef WRAPPER
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport) extern
#endif

namespace MultiLangImportWrapper {

	class Wrapper
	{
	public:
		Wrapper() = default;
		virtual ~Wrapper() = default;
		virtual bool BeginProcess() = 0;

		virtual void UploadProjectInfo(char* filepath, char* projectname) = 0;

		virtual TextData** DownloadTextDataTable() = 0;
		virtual char** DownloadStringArray(const std::string& arrayName) = 0;
		virtual char* DownloadString(const std::string& methodName) = 0;
		virtual wchar_t* DownloadWString(const std::string& methodName) = 0;
		virtual int DownloadInteger(const std::string& variableName) = 0;
		virtual float DownloadFloat(const std::string& variableName) = 0;
		virtual bool DownloadFlag(const std::string& flagName) = 0;


	private:
		Wrapper(const Wrapper&) = delete;
		Wrapper(Wrapper&&) = delete;
		Wrapper& operator=(const Wrapper&) = delete;
		Wrapper& operator=(Wrapper&&) = delete;
	};

	std::unique_ptr<Wrapper> CreateWrapper();
}


extern "C" {
	DLLAPI bool CreateWrapper();
	DLLAPI bool BeginProcess();

	DLLAPI void UploadProjectInfo(char* filepath, char* projectname);

	DLLAPI TextData** DownloadTextDataTable();
	DLLAPI char** DownloadStringArray(const std::string& arrayName);
	DLLAPI char* DownloadString(const std::string& methodName);
	DLLAPI wchar_t* DownloadWString(const std::string& methodName);
	DLLAPI int DownloadInteger(const std::string& variableName);
	DLLAPI float DownloadFloat(const std::string& variableName);
	DLLAPI bool DownloadFlag(const std::string& flagName);
}
