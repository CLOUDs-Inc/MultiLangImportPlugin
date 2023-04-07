#pragma once
#pragma unmanaged
#include <memory>
#include <vector>
#include <string>

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

		virtual char* DownloadString(const std::string& methodName) = 0;


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

	DLLAPI char* DownloadString(const std::string& methodName);
}
