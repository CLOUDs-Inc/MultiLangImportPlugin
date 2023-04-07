#pragma once

extern "C" {
	__declspec(dllexport) BOOL _cdecl MxPlugin_Initialization(HINSTANCE hinstDLL, LPVOID lpvReserved);
	__declspec(dllexport) BOOL _cdecl MxPlugin_Execute(HINSTANCE hinstDLL, LPVOID lpvReserved);
	__declspec(dllexport) BOOL _cdecl MxPlugin_Finalization(HINSTANCE hinstDLL, LPVOID lpvReserved);
	__declspec(dllexport) BOOL _cdecl MxPlugin_GetGUID(HINSTANCE hinstDLL, LPGUID lpGUID, LPVOID lpvReserved);
}

