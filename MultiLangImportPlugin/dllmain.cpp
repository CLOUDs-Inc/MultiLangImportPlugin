#include "pch.h"

/// <summary>
/// pluginインターフェース：初期化処理
/// </summary>
/// <param name="hinstDLL"></param>
/// <param name="lpvReserved"></param>
/// <returns></returns>
BOOL MxPlugin_Initialization(HINSTANCE hinstDLL, LPVOID lpvReserved)
{
	// インポート上コンテキストメニューに起点を登録
	MxPluginPort_System_AddMemu(hinstDLL, (char*)TEXT_MENU_NAME, am_Tool_Plugin, NULL, NULL);

	return TRUE;
}

/// <summary>
/// SDKバージョンチェック処理
/// </summary>
/// <param name="minA">必要最低バージョン１つ目(a.x.x.x)</param>
/// <param name="minB">必要最低バージョン２つ目(x.b.x.x)</param>
/// <param name="minC">必要最低バージョン３つ目(x.x.c.x)</param>
/// <param name="minD">必要最低バージョン４つ目(x.x.x.d)</param>
/// <param name="sdkVersion">SDKバージョン値</param>
/// <returns>true:OK, false:SDKが古い</returns>
bool VersionCheck(int minA, int minB, int minC, int minD, unsigned long long int sdkVersion)
{
	unsigned short* usVer = (unsigned short*)&sdkVersion;
	unsigned short a = usVer[1];
	unsigned short b = usVer[0];
	unsigned short c = usVer[3];
	unsigned short d = usVer[2];

	sdkVersion =
		((unsigned long long int)a) << 48 |
		((unsigned long long int)b) << 32 |
		((unsigned long long int)c) << 16 |
		((unsigned long long int)d);
	unsigned long long int minVersion =
		((unsigned long long int)(0xffff & minA)) << 48 |
		((unsigned long long int)(0xffff & minB)) << 32 |
		((unsigned long long int)(0xffff & minC)) << 16 |
		((unsigned long long int)(0xffff & minD));
	if (minVersion <= sdkVersion) {
		return true;
	}
	// SDK version is too old.
	return false;
}

/// <summary>
/// pluginインターフェース：実行時処理
/// </summary>
/// <param name="hinstDLL"></param>
/// <param name="lpvReserved"></param>
/// <returns></returns>
BOOL MxPlugin_Execute(HINSTANCE hinstDLL, LPVOID lpvReserved)
{
	unsigned long long int	EXEVersion;
	TSDKVersionList			FuncVersion;
	BOOL Flg1 = MxPluginPort_System_GetSDKEXEVersion(&EXEVersion);
	BOOL Flg2 = MxPluginPort_System_GetSDKFuncVersion(&FuncVersion);

	if ((!Flg1) || (!Flg2) || (!VersionCheck(MIN_VER_A, MIN_VER_B, MIN_VER_C, MIN_VER_D, EXEVersion))) {
		MessageBox(MxPluginPort_System_GetHWnd(),
			//				"現在使用しているMatrixEngine SDKでは、このプラグインは動作しません。\n最新のSDKに更新してください。",
			PLUGIN_NAME L" plugin does not work with MatrixEngine SDK currently in use.\nPlease update to the latest MatrixEngine SDK.",
			L"Error", MB_ICONERROR);
		return 1;
	}

	HWND hWnd = MxPluginPort_System_GetHWnd();

	WrapperIf wrapperIf(hWnd, hinstDLL, lpvReserved);
	if (wrapperIf.init())
	{
		wrapperIf.execute();
	}
	wrapperIf.cleanUp();

	return TRUE;
}

/// <summary>
/// pluginインターフェース：終了処理
/// </summary>
/// <param name="hinstDLL"></param>
/// <param name="lpvReserved"></param>
/// <returns></returns>
BOOL MxPlugin_Finalization(HINSTANCE hinstDLL, LPVOID lpvReserved)
{
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return TRUE;
}

/// <summary>
/// pluginインターフェース：GUID取得
/// </summary>
/// <param name="hinstDLL"></param>
/// <param name="lpGUID"></param>
/// <param name="lpvReserved"></param>
/// <returns></returns>
BOOL _cdecl MxPlugin_GetGUID(HINSTANCE hinstDLL, LPGUID lpGUID, LPVOID lpvReserved)
{
	// {F2054633-DD61-4197-B45D-385E02496B54}
	*lpGUID = { 0xf2054633, 0xdd61, 0x4197, { 0xb4, 0x5d, 0x38, 0x5e, 0x2, 0x49, 0x6b, 0x54 } };

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

