#define WRAPPER

#include "MultiLangImportWrapper.h"
#pragma managed

#include "CLITextData.h"
#include <iostream>
#include <string>
#include <gcroot.h>
#include <tchar.h>
#include <msclr/marshal_cppstd.h>

#using <System.dll>
#using <System.Core.dll>
#using <System.Linq.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#using <System.Reflection.dll>
#using <mscorlib.dll>
#using <netstandard.dll>
#using <System.Runtime.dll>

using namespace msclr::interop;
using namespace System;
using namespace System::IO;
using namespace System::Linq;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Reflection;
using namespace System::Collections::Generic;

//void DEBUG_LOG(System::String^ msg) {
//	StreamWriter^ sw = nullptr;
//	try{
//		String^ path = Environment::GetFolderPath(Environment::SpecialFolder::Personal);
//		DirectoryInfo^ dirInfo = gcnew DirectoryInfo(path);
//		//dirInfo = dirInfo->Parent;
//		String^ logPath = dirInfo->ToString() + "\\..\\OutlineBuilder\\sgwrap.log";
//		sw = gcnew StreamWriter(logPath, true);
//
//		sw->WriteLine("[" + System::DateTime::Now + "]" + msg);
//		sw->Flush();
//	}
//	catch (Exception^)
//	{
//
//	}
//	finally{
//		if (sw != nullptr) {
//			sw->Close();
//		}
//	}
//}

namespace MultiLangImportWrapper
{

	public class WrapperImpl : public Wrapper
	{
		const char* GUI_DLL = "\\MultiLangImportDotNet.dll";

	public:
		/// <summary>
		/// ���b�o�[�����N���X�R���X�g���N�^
		/// </summary>
		/// <returns></returns>
		WrapperImpl()
		{
			//DEBUG_LOG("WrapperImpl::WrapperImpl start");
			//MessageBox::Show("WrapperImpl::WrapperImpl start");

			System::String^ loc = Assembly::GetExecutingAssembly()->Location;
			loc = Path::GetDirectoryName(loc) + gcnew System::String(GUI_DLL);
			//DEBUG_LOG("Asm Location: " + loc);
			//MessageBox::Show(loc, "Asm Location");

			Assembly^ assembly;
			try {
				assembly = Assembly::UnsafeLoadFrom(loc);
			}
			catch (System::Exception^) {
				//DEBUG_LOG("WrapperImpl::WrapperImpl LoadForm error: " + e->ToString());
				throw std::exception("DLL Load Error");
			}
			Type^ type = assembly->GetType("MultiLangImportDotNet.ManagedClass");
			Object^ obj = Activator::CreateInstance(type);

			managedObject = obj;
			managedType = type;
			managedTypeTextData = assembly->GetType("MultiLangImportDotNet.Import.TextData");
			//DEBUG_LOG("WrapperImpl::WrapperImpl end");
			//MessageBox::Show("WrapperImpl::WrapperImpl end");
		}

		/// <summary>
		/// �c�[�����O�����J�n
		/// </summary>
		/// <returns></returns>
		bool BeginProcess() override {
			MethodInfo^ methodInfo = managedType->GetMethod("BeginProcess");
			Object^ retObj = methodInfo->Invoke(managedObject, nullptr);
			bool result = safe_cast<bool>(retObj);

			return result;
		}

		/// <summary>
		/// UI���ւ̃v���W�F�N�g�t�@�C���p�X�A���̂̓]��
		/// </summary>
		/// <param name="filepath"></param>
		/// <param name="projectname"></param>
		void UploadProjectInfo(char* filepath, char* projectname) override {
			MethodInfo^ methodInfo = managedType->GetMethod("UploadProjectInfo");

			String^ filepathStr = nullptr;
			if (filepath != nullptr) {
				filepathStr = gcnew String(filepath);
			}
			String^ projectnameStr = nullptr;
			if (projectname != nullptr) {
				projectnameStr = gcnew String(projectname);
			}

			cli::array<Object^>^ args = gcnew cli::array<Object^>(2);
			args[0] = filepathStr;
			args[1] = projectnameStr;
			methodInfo->Invoke(managedObject, args);

			return;
		}

		/// <summary>
		/// .Net������e�L�X�g�L���X�g�f�[�^�i�񎟌��z��j���擾����
		/// �󂯎�葤�͓񎟌��z���������邱��
		/// </summary>
		/// <returns>TextData�񎟌��z��(vector_vector)</returns>
		TextData** DownloadTextDataTable() override {
			System::String^ methodNameManaged = msclr::interop::marshal_as<System::String^>("DownloadTextDataTable");
			MethodInfo^ methodInfo = managedType->GetMethod(methodNameManaged);
			Object^ obj = methodInfo->Invoke(managedObject, nullptr);
			cli::array<Object^, 2>^ tableManaged = safe_cast<cli::array<Object^, 2>^>(obj);

			int rowCount = tableManaged->GetLength(0);
			int colCount = tableManaged->GetLength(1);

			TextData** textDataTable = new TextData*[rowCount]; // �s���m��
			for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
				textDataTable[rowIndex] = new TextData[colCount]; // ����m��
			}

			for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
				for (int colIndex = 0; colIndex < colCount; colIndex++) {
					Object^ objManaged = tableManaged->GetValue(rowIndex, colIndex);
					
					CLITextData^ textDataManaged = safe_cast<CLITextData^>(objManaged);
					
					TextData textData;
					if (textDataManaged == nullptr) {
						// �����Ώۃf�[�^�𖾋L
						textData.isValidData = false;
					}
					else {
						auto textManaged = textDataManaged->text;
						auto fontNameManaged = textDataManaged->fontName;

						textData.text = marshal_as<std::string>(textManaged);
						textData.wtext = marshal_as<std::wstring>(textManaged);
						textData.fontName = marshal_as<std::string>(fontNameManaged);
						textData.fontSize = textDataManaged->fontSize;
						textData.colorR = textDataManaged->colorR;
						textData.colorG = textDataManaged->colorG;
						textData.colorB = textDataManaged->colorB;
						textData.isValidData = true;
						textData.isBold = textDataManaged->isBold;
						textData.isItalic = textDataManaged->isItalic;
						textData.isUnderline = textDataManaged->isUnderline;
						textData.isStrike = textDataManaged->isStrike;
						textData.canConvToANSI = textDataManaged->canConvToANSI;
					}

					textDataTable[rowIndex][colIndex] = textData;
				}
			}

			return textDataTable;
		}

		/// <summary>
		/// .Net����蕶����z��f�[�^���擾����i�߂�l�󂯎�葤��delete[]���K�v
		/// </summary>
		/// <param name="arrayName">������z��</param>
		/// <returns>������z��f�[�^</returns>
		char** DownloadStringArray(const std::string& arrayName) override {
			System::String^ methodNameManaged = msclr::interop::marshal_as<System::String^>("Download" + arrayName);
			MethodInfo^ methodInfo = managedType->GetMethod(methodNameManaged);
			Object^ obj = methodInfo->Invoke(managedObject, nullptr);
			cli::array<String^>^ strArrayManaged = safe_cast<cli::array<String^>^>(obj);
			
			int arrayCount = strArrayManaged->GetLength(0);

			char** strArray = new char* [arrayCount];
			for (int index = 0; index < arrayCount; index++)
			{
				auto strManaged = strArrayManaged[index];
				std::string stringUnmanaged = marshal_as<std::string>(strManaged);
				size_t bufLen = stringUnmanaged.length() + 1;
				char* pStr = new char[bufLen];
				strcpy_s(pStr, bufLen, stringUnmanaged.c_str());
				strArray[index] = pStr;
			}

			return strArray;
		}

		/// <summary>
		/// .NET����蕶����f�[�^�̎擾�i���ʏ����A�߂�l�󂯎�葤��delete[]���K�v
		/// </summary>
		/// <param name="methodName">������擾���\�b�h��</param>
		/// <returns>������f�[�^</returns>
		char* DownloadString(const std::string& methodName) override {
			System::String^ methodNameManaged = msclr::interop::marshal_as<System::String^>(methodName);
			MethodInfo^ methodInfo = managedType->GetMethod(methodNameManaged);
			Object^ obj = methodInfo->Invoke(managedObject, nullptr);
			String^ stringManaged = safe_cast<String^>(obj);

			std::string stringUnmanaged = marshal_as<std::string>(stringManaged);
			size_t bufLen = stringUnmanaged.length() + 1;
			char* pStr = new char[bufLen];
			strcpy_s(pStr, bufLen, stringUnmanaged.c_str());

			return pStr;
		}

		/// <summary>
		/// .NET����胏�C�h������f�[�^�̎擾�i���ʏ����A�߂�l�󂯎�葤��delete[]���K�v
		/// </summary>
		/// <param name="methodName">������擾���\�b�h��</param>
		/// <returns>������f�[�^</returns>
		wchar_t* DownloadWString(const std::string& methodName) override {
			System::String^ methodNameManaged = msclr::interop::marshal_as<System::String^>(methodName);
			MethodInfo^ methodInfo = managedType->GetMethod(methodNameManaged);
			Object^ obj = methodInfo->Invoke(managedObject, nullptr);
			String^ stringManaged = safe_cast<String^>(obj);

			std::wstring wstringUnmanaged = marshal_as<std::wstring>(stringManaged);
			size_t bufLen = wstringUnmanaged.length() + 1;
			wchar_t* pwStr = new wchar_t[bufLen];
			wcscpy_s(pwStr, bufLen, wstringUnmanaged.c_str());

			return pwStr;
		}

		/// <summary>
		/// .Net������integer�f�[�^���擾����
		/// </summary>
		/// <param name="variableName">�擾��ϐ���</param>
		/// <returns>int�f�[�^</returns>
		int DownloadInteger(const std::string& variableName) override {
			System::String^ methodNameManaged = msclr::interop::marshal_as<System::String^>("Download" + variableName);
			MethodInfo^ methodInfo = managedType->GetMethod(methodNameManaged);
			Object^ obj = methodInfo->Invoke(managedObject, nullptr);
			int val = safe_cast<int>(obj);
			return val;
		}

		/// <summary>
		/// .Net������float�f�[�^���擾����
		/// </summary>
		/// <param name="variableName">�擾��ϐ���</param>
		/// <returns>float�f�[�^</returns>
		float DownloadFloat(const std::string& variableName) override {
			System::String^ methodNameManaged = msclr::interop::marshal_as<System::String^>("Download" + variableName);
			MethodInfo^ methodInfo = managedType->GetMethod(methodNameManaged);
			Object^ obj = methodInfo->Invoke(managedObject, nullptr);
			float val = safe_cast<float>(obj);
			return val;
		}

		/// <summary>
		/// .Net������t���O�f�[�^���擾����
		/// </summary>
		/// <param name="flagName"></param>
		/// <returns></returns>
		bool DownloadFlag(const std::string& flagName) override {
			bool flag = false;

			System::String^ methodNameManaged = msclr::interop::marshal_as<System::String^>("DownloadFlag");
			MethodInfo^ methodInfo = managedType->GetMethod(methodNameManaged);

			String^ flagNameStr = nullptr;
			flagNameStr = gcnew String(flagName.c_str());
			if (flagNameStr != nullptr) {
				cli::array<Object^>^ args = gcnew cli::array<Object^>(1);
				args[0] = flagNameStr;
				Object^ obj = methodInfo->Invoke(managedObject, args);
				flag = safe_cast<bool>(obj);
			}

			return flag;
		}


	private:
		gcroot<Object^> managedObject;
		gcroot<Type^> managedType;
		gcroot<Type^> managedTypeTextData;
	};

	/// <summary>
	/// GUI�Ƃ�IF���b�p�[�̐����擾
	/// </summary>
	/// <returns></returns>
	std::unique_ptr<Wrapper> CreateWrapper()
	{
		std::unique_ptr<Wrapper> wrapperImpl;
		try {
			wrapperImpl = std::make_unique<WrapperImpl>();

		}
		catch (std::exception& e) {
			throw e;
		}
		return wrapperImpl;
	}
}

std::unique_ptr<MultiLangImportWrapper::Wrapper> wrapper = nullptr;

/// <summary>
/// ���b�p�[����
/// </summary>
/// <returns></returns>
bool CreateWrapper() {
	bool result = false;

	try {
		//DEBUG_LOG("::CreateWrapper start");
		wrapper = MultiLangImportWrapper::CreateWrapper();
		result = true;
	}
	catch (std::exception&) {
		wrapper = nullptr;
		result = false;
	}

	return result;
}

/// <summary>
/// �c�[�����O�����J�n
/// </summary>
/// <returns></returns>
bool BeginProcess()
{
	if (wrapper != nullptr)
	{
		return wrapper->BeginProcess();
	}
	return false;
}

/// <summary>
/// UI���ւ̃v���W�F�N�g�t�@�C���p�X�A���̂̓]��
/// </summary>
/// <param name="filepath">�v���W�F�N�g�t�@�C���p�X</param>
/// <param name="projectname">�v���W�F�N�g��</param>
void UploadProjectInfo(char* filepath, char* projectname)
{
	if (wrapper != nullptr)
	{
		wrapper->UploadProjectInfo(filepath, projectname);
	}
}

/// <summary>
/// .Net������̑�����C���|�[�g�e�L�X�g�L���X�g�f�[�^�̎擾
/// </summary>
/// <returns>�e�L�X�g�L���X�g�f�[�^�e�[�u���i�񎟌��z��B�󂯎�葤��delete������邱�Ɓj</returns>
TextData** DownloadTextDataTable()
{
	if (wrapper != nullptr) {
		return wrapper->DownloadTextDataTable();
	}
	return nullptr;
}

/// <summary>
/// .Net������̕�����z��̎擾
/// </summary>
/// <param name="arrayName">������z��</param>
/// <returns>������z��i�󂯎�葤��delete������邱�Ɓj</returns>
char** DownloadStringArray(const std::string& arrayName)
{
	if (wrapper != nullptr) {
		return wrapper->DownloadStringArray(arrayName);
	}
	return nullptr;
}

/// <summary>
/// .NET������̕�����̎擾
/// </summary>
/// <param name="methodName">.NET��������o�̓��\�b�h��</param>
/// <returns>������</returns>
char* DownloadString(const std::string& methodName)
{
	if (wrapper != nullptr) {
		return wrapper->DownloadString(methodName);
	}
	return nullptr;
}

/// <summary>
/// .NET������̃��C�h������̎擾
/// </summary>
/// <param name="methodName">.NET��������o�̓��\�b�h��</param>
/// <returns>������</returns>
wchar_t* DownloadWString(const std::string& methodName)
{
	if (wrapper != nullptr) {
		return wrapper->DownloadWString(methodName);
	}
	return nullptr;
}

/// <summary>
/// .Net������̐����̎擾
/// </summary>
/// <param name="variableName">.Net���ϐ���</param>
/// <returns>�����l</returns>
int DownloadInteger(const std::string& variableName)
{
	if (wrapper != nullptr) {
		return wrapper->DownloadInteger(variableName);
	}
	return -1;
}

/// <summary>
/// .Net�������float�l�̎擾
/// </summary>
/// <param name="variableName">.Net���ϐ���</param>
/// <returns>float�l</returns>
float DownloadFloat(const std::string& variableName)
{
	if (wrapper != nullptr) {
		return wrapper->DownloadFloat(variableName);
	}
	return -1.0f;
}

/// <summary>
/// .Net������t���O(bool)�l�̎擾
/// </summary>
/// <param name="flagName">�t���O��</param>
/// <returns>�t���O�^�U�l</returns>
bool DownloadFlag(const std::string& flagName)
{
	if (wrapper != nullptr) {
		return wrapper->DownloadFlag(flagName);
	}
	return false;
}
