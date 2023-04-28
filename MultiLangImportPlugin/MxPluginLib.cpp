#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include "MxPluginLib.h"

#define IDMxPluginPort_System_Version					0x00
#define IC_Port_System_Version					  0x00000001
#define IDMxPluginPort_System_AddMemu					0x01
#define IDMxPluginPort_System_Paint						0x02
#define IDMxPluginPort_System_AttachEvent				0x03
#define	IDMxPluginPort_System_GetHWnd					0x04
#define	IDMxPluginPort_System_Progress					0x06
#define	IDMxPluginPort_System_TrimLabelName				0x07
#define	IDMxPluginPort_System_GetSDKVersion				0x08	//2016.01.25
#define	IDMxPluginPort_System_GetSDKLanguage			0x09	//2017.07.06
#define	IDMxPluginPort_System_ProcessMessages			0x0A	//2020.03.26
#define	IDMxPluginPort_System_MenuEnabled				0x100	//2020.03.17
#define	IDMxPluginPort_System_MenuVisible				0x101	//2020.03.17
#define	IDMxPluginPort_System_MenuCaption				0x102	//2020.03.17
#define	IDMxPluginPort_Event_GetUIHandle				0x200
#define	IDMxPluginPort_Event_GetEventType				0x201
#define	IDMxPluginPort_Event_GetPreEvent				0x202
#define	IDMxPluginPort_Event_GetMXPFileName				0x203

#define	IDMxPluginPort_Event_Score_GetScoreTrack		0x300
#define	IDMxPluginPort_Event_Score_GetSelectedCount		0x301
#define	IDMxPluginPort_Event_Score_GetSelectedTrack		0x302

#define	IDMxPluginPort_Event_ScoreRename_GetNumber		0x310
#define	IDMxPluginPort_Event_ScoreRename_GetOldName		0x311
#define	IDMxPluginPort_Event_ScoreRename_GetNewName		0x312

#define	IDMxPluginPort_Event_Cast_GetCastType			0x400
#define	IDMxPluginPort_Event_Cast_GetCastNumber			0x401
#define	IDMxPluginPort_Event_Cast_GetOldName			0x402
#define	IDMxPluginPort_Event_Cast_GetNewName			0x403

#define IDMxPluginPort_Project_Init						0x10
#define IDMxPluginPort_Project_LoadCabinet				0x11
#define IDMxPluginPort_Project_LoadCabinetEx			0x12
#define IDMxPluginPort_Project_SetScreenSize			0x13
#define IDMxPluginPort_Project_GetContentsPath			0x14
#define IDMxPluginPort_Project_GetContentsName			0x15
#define IDMxPluginPort_Project_GetContentsSaved			0x16
#define IDMxPluginPort_Project_SaveContents				0x17
#define IDMxPluginPort_Project_LoadContents				0x18
#define IDMxPluginPort_Project_GetContentsChanged		0x19
#define IDMxPluginPort_Project_CreateRuntimeFile		0x1A
#define IDMxPluginPort_Project_GetContentsRunning		0x1B
#define IDMxPluginPort_Project_SetContentsChanged		0x1C
#define IDMxPluginPort_Project_ClearContentsChanged		0x1D
#define	IDMxPluginPort_Project_LoadFile					0x1E

#define IDMxPluginPort_CLang_GetEnabled					0x500
#define IDMxPluginPort_CLang_GetPathSRC					0x501
#define IDMxPluginPort_CLang_GetPathEvent				0x502
#define IDMxPluginPort_CLang_GetPathLib					0x503
#define IDMxPluginPort_CLang_GetPathOBJ					0x504
#define	IDMxPluginPort_CLang_GetFileNameConst			0x505
#define	IDMxPluginPort_CLang_GetFileNameEventSource		0x506
#define	IDMxPluginPort_CLang_GetFileNameEventHeader		0x507

#define	IDMxPluginPort_CLang_GetInitEvent_Enabled		0x510
#define	IDMxPluginPort_CLang_GetInitEvent_Type			0x511
#define	IDMxPluginPort_CLang_GetInitEvent_Name			0x512
#define	IDMxPluginPort_CLang_GetFinallyEvent_Enabled	0x513
#define	IDMxPluginPort_CLang_GetFinallyEvent_Type		0x514
#define	IDMxPluginPort_CLang_GetFinallyEvent_Name		0x515
#define	IDMxPluginPort_CLang_GetInitEventFuncName		0x516
#define	IDMxPluginPort_CLang_GetFinallyEventFuncName	0x517

#define	IDMxPluginPort_CLang_SetEnabled					0x580
#define	IDMxPluginPort_CLang_SetPathSRCNative			0x581
#define	IDMxPluginPort_CLang_SetPathEventNative			0x582
#define	IDMxPluginPort_CLang_SetPathLibNative			0x583
#define	IDMxPluginPort_CLang_SetPathOBJNative			0x584
#define	IDMxPluginPort_CLang_GetPathSRCNative			0x585
#define	IDMxPluginPort_CLang_GetPathEventNative			0x586
#define	IDMxPluginPort_CLang_GetPathLibNative			0x587
#define	IDMxPluginPort_CLang_GetPathOBJNative			0x588

#define	IDMxPluginPort_CLang_SetInitEvent_Enabled		0x590
#define	IDMxPluginPort_CLang_SetInitEvent_Type			0x591
#define	IDMxPluginPort_CLang_SetInitEvent_Name			0x592
#define	IDMxPluginPort_CLang_SetFinallyEvent_Enabled	0x593
#define	IDMxPluginPort_CLang_SetFinallyEvent_Type		0x594
#define	IDMxPluginPort_CLang_SetFinallyEvent_Name		0x595

#define	IDMxPluginPort_CLang_SetEventListName_Type		0x598
#define	IDMxPluginPort_CLang_SetEventListName_Name		0x599
#define	IDMxPluginPort_CLang_SetEventSymbolName_Type	0x59A
#define	IDMxPluginPort_CLang_SetEventSymbolName_Name	0x59B
#define	IDMxPluginPort_CLang_SetEventTableName_Type		0x59C
#define	IDMxPluginPort_CLang_SetEventTableName_Name		0x59D
#define	IDMxPluginPort_CLang_SetEventTableName_Alias	0x59E

#define	IDMxPluginPort_Project_MultiLang_GetEnabled		0x8000
#define	IDMxPluginPort_Project_MultiLang_SetEnabled		0x8001
#define	IDMxPluginPort_Project_MultiLang_GetCount		0x8002
#define	IDMxPluginPort_Project_MultiLang_GetName		0x8003
#define	IDMxPluginPort_Project_MultiLang_SetName		0x8004
#define	IDMxPluginPort_Project_MultiLang_Add			0x8005
#define	IDMxPluginPort_Project_MultiLang_Remove			0x8006

#define IDMxPluginPort_Cast_FindBlank					0x20
#define IDMxPluginPort_Cast_FindBlankSince				0x21
#define IDMxPluginPort_Cast_GetCastCount				0x22
#define IDMxPluginPort_Cast_CreateCamera				0x23
#define IDMxPluginPort_Cast_CreateLight					0x24
#define IDMxPluginPort_Cast_Delete						0x25
#define IDMxPluginPort_Cast_UseCheck					0x26
#define IDMxPluginPort_Cast_GetCastName					0x27
#define IDMxPluginPort_Cast_SetCastName					0x28
#define IDMxPluginPort_Cast_SaveToFile					0x29
#define IDMxPluginPort_Cast_FindCast					0x2A
#define IDMxPluginPort_Cast_CreateWave					0x2B
#define IDMxPluginPort_Cast_CreateText					0x2C
#define IDMxPluginPort_Cast_CreateScript				0x2D
#define IDMxPluginPort_Cast_CreateTexture				0x2E
#define IDMxPluginPort_Cast_CreateBitmap				0x2F
#define IDMxPluginPort_Cast_CreateTextureEx				0x30
#define IDMxPluginPort_Cast_Assigned					0x31
#define IDMxPluginPort_Cast_TrimCastName				0x32
#define IDMxPluginPort_Cast_TrimFileName				0x33
#define	IDMxPluginPort_Cast_Exchange					0x34
#define IDMxPluginPort_Cast_CreateScriptEx				0x35

#define IDMxPluginPort_Score_GetScoreName				0x40
#define IDMxPluginPort_Score_GetScoreCount				0x41
#define IDMxPluginPort_Score_GetTrackCount				0x42
#define IDMxPluginPort_Score_CreateScore				0x43
#define IDMxPluginPort_Score_CreateTrack				0x44
//0x45,0x46は下で使用
#define IDMxPluginPort_Score_DeleteTrack				0x47
#define IDMxPluginPort_Score_Trim						0x48
#define IDMxPluginPort_Score_GetLength					0x49
#define IDMxPluginPort_Score_Find						0x4A
#define IDMxPluginPort_Score_UpdatdeLength				0x4B
#define IDMxPluginPort_Score_Exchange					0x4C
#define IDMxPluginPort_Score_DeleteScore				0x4D
#define IDMxPluginPort_Score_GetLabel					0x4E	//2014.10.02
#define IDMxPluginPort_Score_SetLabel					0x4F	//2014.10.02
#define IDMxPluginPort_Score_GetLabelPosMax				0x50	//2015.11.27
#define IDMxPluginPort_Score_FindFrameLabel				0x51	//2015.11.27
#define IDMxPluginPort_Score_Clear						0x52	//2015.11.27
#define IDMxPluginPort_Score_SetAnnotationEncode		0x53
#define IDMxPluginPort_Score_SetAnnotationData			0x54
#define IDMxPluginPort_Score_GetAnnotationEncode		0x55
#define IDMxPluginPort_Score_GetAnnotationData			0x56
#define IDMxPluginPort_Score_GetAnnotationCount			0x57
#define IDMxPluginPort_Score_ClearAnnotation			0x58
#define IDMxPluginPort_Score_InsertAnnotationData		0x59
#define IDMxPluginPort_Score_RemoveAnnotationData		0x5A
#define IDMxPluginPort_Score_MoveTrack					0x5B

#define IDMxPluginPort_Track_GetCastType				0x45
#define IDMxPluginPort_Track_GetCastNumber				0x46
#define IDMxPluginPort_Track_GetLength					0x60
#define IDMxPluginPort_Track_GetParent					0x61
#define IDMxPluginPort_Track_GetFrameData				0x62
#define IDMxPluginPort_Track_SetFrameData				0x63
#define IDMxPluginPort_Track_Trim						0x64
#define IDMxPluginPort_Track_SetParent					0x65
#define IDMxPluginPort_Track_TestSetParent				0x66
#define IDMxPluginPort_Track_Assigned					0x67
#define IDMxPluginPort_Track_FindBlank					0x68
#define IDMxPluginPort_Track_SetAttribute				0x69	//2014.04.09
#define IDMxPluginPort_Track_GetAttribute				0x6A	//2014.04.09
#define IDMxPluginPort_Track_GetLabelName				0x6B	//2014.10.01
#define IDMxPluginPort_Track_SetLabelName				0x6C	//2014.10.01
#define IDMxPluginPort_Track_SetCastNumber				0x6D	//2014.10.07
#define IDMxPluginPort_Track_FindTrackLabel				0x6E	//2015.11.27

#define IDMxPluginPort_TrackProperty_SetData			0x70
#define IDMxPluginPort_TrackProperty_GetData			0x71

#define IDMxPluginPort_LoopTrack_GetLength				0x80
#define IDMxPluginPort_LoopTrack_GetValue				0x81
#define IDMxPluginPort_LoopTrack_SetValue				0x82
#define IDMxPluginPort_LoopTrack_Trim					0x83

#define IDMxPluginPort_CastPropety_SetData				0x90
#define IDMxPluginPort_CastPropety_GetData				0x91
#define IDMxPluginPort_CastPropety_SetData2				0x92
#define IDMxPluginPort_CastPropety_SetData3				0x93

#define IDMxPluginPort_Primitive_QuadPolygon			0xA0

#define IDMxPluginPort_Project_SetPropertyInt			0x700
#define IDMxPluginPort_Project_GetPropertyInt			0x701

#define	IDMxPluginPort_Cast_Text_GetLineCount			0x1000
#define	IDMxPluginPort_Cast_Text_GetLineString			0x1001

#define	IDMxPluginPort_Cast_TextML_GetLangAssigned		0x1800
#define	IDMxPluginPort_Cast_TextML_CreateLanguage		0x1801
#define	IDMxPluginPort_Cast_TextML_RemoveLanguage		0x1802

#define	IDMxPluginPort_End								0xFF

//========================================
//サービス関数の型定義
//========================================

typedef BOOL(_cdecl* TMxPluginPort_System_AddMemu)(HINSTANCE hinstDLL, char* Name, int Option, void* Reserved, void* UserParam);
typedef BOOL(_cdecl* TMxPluginPort_System_MenuEnabled)(int hinstMenu, BOOL Enabled);
typedef BOOL(_cdecl* TMxPluginPort_System_MenuVisible)(int hinstMenu, BOOL Visible);
typedef BOOL(_cdecl* TMxPluginPort_System_MenuCaption)(int hinstMenu, char* Caption);

typedef BOOL(_cdecl* TMxPluginPort_System_Paint)(void* Reserved);
typedef BOOL(_cdecl* TMxPluginPort_System_AttachEvent)(HINSTANCE hinstDLL, UINT msg, TMxWMCOPYDATAPROC lpWMCopyDataProc);
typedef HWND(_cdecl* TMxPluginPort_System_GetHWnd)(void);
typedef BOOL(_cdecl* TMxPluginPort_System_Progress)(int Command, int Param);
typedef BOOL(_cdecl* TMxPluginPort_System_ProgressMsg)(int Command, char* Msg);
typedef BOOL(_cdecl* TMxPluginPort_System_TrimLabelName)(char* Des, char* Sou);
typedef BOOL(_cdecl* TMxPluginPort_System_GetSDKVersion)(int Mode, void* Version);
typedef int(_cdecl* TMxPluginPort_System_GetSDKLanguage)(void);
typedef BOOL(_cdecl* TMxPluginPort_System_ProcessMessages)(void);
typedef BOOL(_cdecl* TMxPluginPort_Event_GetUIHandle)(HINSTANCE hinstDLL, int* Handle);
typedef BOOL(_cdecl* TMxPluginPort_Event_GetEventType)(HINSTANCE hinstDLL, int* Type);
typedef BOOL(_cdecl* TMxPluginPort_Event_GetPreEvent)(HINSTANCE hinstDLL, BOOL* Flag);
typedef BOOL(_cdecl* TMxPluginPort_Event_GetMXPFileName)(HINSTANCE hinstDLL, char** FileName);

typedef BOOL(_cdecl* TMxPluginPort_Event_Score_GetScoreTrack)(HINSTANCE hinstDLL, int* ScoreNumber, int* TrackNumber);
typedef BOOL(_cdecl* TMxPluginPort_Event_Score_GetSelectedCount)(HINSTANCE hinstDLL, int* SelectedCount);
typedef BOOL(_cdecl* TMxPluginPort_Event_Score_GetSelectedTrack)(HINSTANCE hinstDLL, int Index, int* TrackNum);

typedef BOOL(_cdecl* TMxPluginPort_Event_ScoreRename_GetNumber)(HINSTANCE hinstDLL, int* ScoreNum);
typedef BOOL(_cdecl* TMxPluginPort_Event_ScoreRename_GetOldName)(HINSTANCE hinstDLL, char** OldName);
typedef BOOL(_cdecl* TMxPluginPort_Event_ScoreRename_GetNewName)(HINSTANCE hinstDLL, char** NewName);

typedef BOOL(_cdecl* TMxPluginPort_Event_Cast_GetCastType)(HINSTANCE hinstDLL, int* CastType);
typedef BOOL(_cdecl* TMxPluginPort_Event_Cast_GetCastNumber)(HINSTANCE hinstDLL, int* CastNumber);
typedef BOOL(_cdecl* TMxPluginPort_Event_Cast_GetOldName)(HINSTANCE hinstDLL, char** OldName);
typedef BOOL(_cdecl* TMxPluginPort_Event_Cast_GetNewName)(HINSTANCE hinstDLL, char** NewName);

typedef BOOL(_cdecl* TMxPluginPort_Project_Init)(int InitMode);
typedef BOOL(_cdecl* TMxPluginPort_Project_LoadCabinet)(char* FileName, int Mode);
typedef BOOL(_cdecl* TMxPluginPort_Project_LoadCabinetEx)(char* FileName, int Mode, int* ScoreNumber, int* TrackNumber);
typedef BOOL(_cdecl* TMxPluginPort_Project_SetScreenSize)(int width, int height);
typedef char* (_cdecl* TMxPluginPort_Project_GetContentsPath)(void);
typedef char* (_cdecl* TMxPluginPort_Project_GetContentsName)(void);
typedef BOOL(_cdecl* TMxPluginPort_Project_GetContentsSaved)(void);
typedef BOOL(_cdecl* TMxPluginPort_Project_SaveContents)(char* FileName);
typedef BOOL(_cdecl* TMxPluginPort_Project_LoadContents)(char* FileName);
typedef BOOL(_cdecl* TMxPluginPort_Project_GetContentsChanged)(void);
typedef BOOL(_cdecl* TMxPluginPort_Project_SetContentsChanged)(void);
typedef BOOL(_cdecl* TMxPluginPort_Project_ClearContentsChanged)(void);
typedef BOOL(_cdecl* TMxPluginPort_Project_CreateRuntimeFile)(char* FileName, int Format, void* Options);
typedef BOOL(_cdecl* TMxPluginPort_Project_GetContentsRunning)(void);
typedef BOOL(_cdecl* TMxPluginPort_Project_LoadFile)(char* FileName, int Format, void* Options);

typedef BOOL(_cdecl* TMxPluginPort_CLang_GetEnabled)(void);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetPathSRC)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetPathEvent)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetPathLib)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetPathOBJ)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetFileNameConst)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetFileNameEventSource)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetFileNameEventHeader)(char** FileName);

typedef BOOL(_cdecl* TMxPluginPort_CLang_GetInitEvent_Enabled)(BOOL* Enabled);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetInitEvent_Type)(int* Type);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetInitEvent_Name)(char** Name);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetFinallyEvent_Enabled)(BOOL* Enabled);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetFinallyEvent_Type)(int* Type);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetFinallyEvent_Name)(char** Name);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetInitEventFuncName)(char** Name);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetFinallyEventFuncName)(char** Name);

typedef BOOL(_cdecl* TMxPluginPort_CLang_SetEnabled)(BOOL Enabled);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetPathSRCNative)(char* FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetPathEventNative)(char* FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetPathLibNative)(char* FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetPathOBJNative)(char* FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetPathSRCNative)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetPathEventNative)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetPathLibNative)(char** FileName);
typedef BOOL(_cdecl* TMxPluginPort_CLang_GetPathOBJNative)(char** FileName);

typedef BOOL(_cdecl* TMxPluginPort_CLang_SetInitEvent_Enabled)(BOOL Enabled);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetInitEvent_Type)(int  Type);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetInitEvent_Name)(char* Name);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetFinallyEvent_Enabled)(BOOL Enabled);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetFinallyEvent_Type)(int  Type);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetFinallyEvent_Name)(char* Name);

typedef BOOL(_cdecl* TMxPluginPort_CLang_SetEventListName_Type)(int	Value);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetEventListName_Name)(char* Name);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetEventSymbolName_Type)(int	Value);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetEventSymbolName_Name)(char* Name);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetEventTableName_Type)(int	Value);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetEventTableName_Name)(char* Name);
typedef BOOL(_cdecl* TMxPluginPort_CLang_SetEventTableName_Alias)(BOOL Enabled);

typedef	BOOL(_cdecl* TMxPluginPort_Project_MultiLang_GetEnabled)(BOOL* Enabled);
typedef	BOOL(_cdecl* TMxPluginPort_Project_MultiLang_SetEnabled)(BOOL	Enabled);
typedef	BOOL(_cdecl* TMxPluginPort_Project_MultiLang_GetCount)(int* Count);
typedef	BOOL(_cdecl* TMxPluginPort_Project_MultiLang_GetName)(int	Index, char** Name);
typedef	BOOL(_cdecl* TMxPluginPort_Project_MultiLang_SetName)(int	Index, const char* Name);
typedef	BOOL(_cdecl* TMxPluginPort_Project_MultiLang_Add)(const char* Name);
typedef	BOOL(_cdecl* TMxPluginPort_Project_MultiLang_Remove)(int	Index);

typedef int(_cdecl* TMxPluginPort_Cast_FindBlank)(int CastType);
typedef int(_cdecl* TMxPluginPort_Cast_FindBlankSince)(int CastType, int CastNumber);
typedef int(_cdecl* TMxPluginPort_Cast_GetCastCount)(int CastType);
typedef int(_cdecl* TMxPluginPort_Cast_CreateCamera)(int CastNumber, char* CastName);
typedef int(_cdecl* TMxPluginPort_Cast_CreateLight)(int CastNumber, char* CastName, int LightType);
typedef BOOL(_cdecl* TMxPluginPort_Cast_Delete)(int CastType, int CastNumber, int Reserved);
typedef BOOL(_cdecl* TMxPluginPort_Cast_UseCheck)(int CastType, int CastNumber);
typedef int(_cdecl* TMxPluginPort_Cast_GetCastName)(int CastType, int CastNumber, char* CastName, int NameLength);
typedef int(_cdecl* TMxPluginPort_Cast_SetCastName)(int CastType, int CastNumber, char* NewName, BOOL OverWrite);
typedef BOOL(_cdecl* TMxPluginPort_Cast_SaveToFile)(int CastType, int CastNumbe, char* FileName, void* Reserved);
typedef int(_cdecl* TMxPluginPort_Cast_FindCast)(int CastType, char* CastName);
typedef int(_cdecl* TMxPluginPort_Cast_CreateWave)(int CastNumber, char* CastName, char* FileName, BOOL ExternalFile);
typedef int(_cdecl* TMxPluginPort_Cast_CreateText)(int CastNumber, char* CastName);
typedef int(_cdecl* TMxPluginPort_Cast_CreateScript)(int CastNumber, char* CastName);
typedef int(_cdecl* TMxPluginPort_Cast_CreateScriptEx)(int CastNumber, char* CastName, char* FileName, int Options, int Reserved);
typedef int(_cdecl* TMxPluginPort_Cast_CreateTexture)(int CastNumber, char* CastName, char* FileName);
typedef int(_cdecl* TMxPluginPort_Cast_CreateTextureEx)(int CastNumber, char* CastName, char* FileName, int Option, int Reserved);
typedef int(_cdecl* TMxPluginPort_Cast_CreateBitmap)(int CastNumber, char* CastName, char* FileName);
typedef BOOL(_cdecl* TMxPluginPort_Cast_Assigned)(int CastType, int CastNumber);
typedef int(_cdecl* TMxPluginPort_Cast_TrimCastName)(int CastType, char* SourCastName, char* DestCastName, int NameLength);
typedef BOOL(_cdecl* TMxPluginPort_Cast_TrimFileName)(int CastType, int CastNumber);
typedef BOOL(_cdecl* TMxPluginPort_Cast_Exchange)(int CastType, int CastNumber1, int CastNumber2);

typedef int(_cdecl* TMxPluginPort_Score_GetScoreName)(int ScoreNumber, char* ScoreName, int NameLength);
typedef int(_cdecl* TMxPluginPort_Score_GetScoreCount)(void);
typedef int(_cdecl* TMxPluginPort_Score_GetTrackCount)(int ScoreNumber);
typedef int(_cdecl* TMxPluginPort_Score_CreateScore)(char* ScoreName, int* TrackNumber);
typedef int(_cdecl* TMxPluginPort_Score_CreateTrack)(int ScoreNumber, int CastType, int CastNumber);
typedef BOOL(_cdecl* TMxPluginPort_Score_DeleteTrack)(int ScoreNumber, int TrackNumber, int Reserved);
typedef BOOL(_cdecl* TMxPluginPort_Score_Trim)(int ScoreNumber);
typedef int(_cdecl* TMxPluginPort_Score_GetLength)(int ScoreNumber);
typedef int(_cdecl* TMxPluginPort_Score_Find)(char* ScoreName);
typedef BOOL(_cdecl* TMxPluginPort_Score_UpdateLength)(int ScoreNumber);
typedef BOOL(_cdecl* TMxPluginPort_Score_Exchange)(int ScoreNumber, int Track1, int Track2);
typedef BOOL(_cdecl* TMxPluginPort_Score_DeleteScore)(int ScoreNumber);
typedef int(_cdecl* TMxPluginPort_Score_GetLabelName)(int ScoreNumber, int FrameNumber, char* LabelName, int NameLength);
typedef BOOL(_cdecl* TMxPluginPort_Score_SetLabelName)(int ScoreNumber, int FrameNumber, char* LabelName, int Reserved);
typedef int(_cdecl* TMxPluginPort_Score_GetLabelPosMax)(int ScoreNumber);
typedef int(_cdecl* TMxPluginPort_Score_FindFrameLabel)(int ScoreNumber, char* LabelName);
typedef BOOL(_cdecl* TMxPluginPort_Score_Clear)(int ScoreNumber, int Options);
typedef BOOL(_cdecl* TMxPluginPort_Score_MoveTrack)(int ScoreNumber, int MoveTo, int MoveFrom);

typedef BOOL(_cdecl* TMxPluginPort_Score_SetAnnotationEncode)(int ScoreNumber, int Encode);
typedef BOOL(_cdecl* TMxPluginPort_Score_SetAnnotationData)(int ScoreNumber, int Page, void* Annotation);
typedef BOOL(_cdecl* TMxPluginPort_Score_GetAnnotationEncode)(int ScoreNumber, int* Encode);
typedef BOOL(_cdecl* TMxPluginPort_Score_GetAnnotationData)(int ScoreNumber, int Page, void** Annotation);
typedef BOOL(_cdecl* TMxPluginPort_Score_GetAnnotationCount)(int ScoreNumber, int* Count);
typedef BOOL(_cdecl* TMxPluginPort_Score_ClearAnnotation)(int ScoreNumber, int Page);
typedef int(_cdecl* TMxPluginPort_Score_InsertAnnotationData)(int ScoreNumber, int Page, void* Annotation);
typedef BOOL(_cdecl* TMxPluginPort_Score_RemoveAnnotationData)(int ScoreNumber, int Page);

typedef BOOL(_cdecl* TMxPluginPort_Track_GetCastType)(int ScoreNumber, int TrackNumber, int* CastType);
typedef BOOL(_cdecl* TMxPluginPort_Track_GetCastNumber)(int ScoreNumber, int TrackNumber, int* CastNumber);
typedef BOOL(_cdecl* TMxPluginPort_Track_SetCastNumber)(int ScoreNumber, int TrackNumber, int CastNumber);
typedef int(_cdecl* TMxPluginPort_Track_GetLength)(int ScoreNumber, int TrackNumber);
typedef BOOL(_cdecl* TMxPluginPort_Track_GetParent)(int ScoreNumber, int TrackNumber, int* ParentTrackNumber);
typedef BOOL(_cdecl* TMxPluginPort_Track_TestSetParent)(int ScoreNumber, int ParentTrack, int ChildTrack);
typedef BOOL(_cdecl* TMxPluginPort_Track_SetParent)(int ScoreNumber, int ParentTrack, int ChildTrack);
typedef BOOL(_cdecl* TMxPluginPort_Track_GetFrameData)(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType, void* Data);
typedef BOOL(_cdecl* TMxPluginPort_Track_SetFrameData)(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType, void* Data);
typedef BOOL(_cdecl* TMxPluginPort_Track_Trim)(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType);
typedef BOOL(_cdecl* TMxPluginPort_Track_Assigned)(int ScoreNumber, int TrackNumber);
typedef int(_cdecl* TMxPluginPort_Track_FindBlank)(int ScoreNumber);
typedef BOOL(_cdecl* TMxPluginPort_Track_SetAttribute)(int ScoreNumber, int TrackNumber, int AttrType, BOOL Value);
typedef BOOL(_cdecl* TMxPluginPort_Track_GetAttribute)(int ScoreNumber, int TrackNumber, int AttrType, BOOL* Value);
typedef int(_cdecl* TMxPluginPort_Track_GetLabelName)(int ScoreNumber, int TrackNumber, char* LabelName, int NameLength);
typedef BOOL(_cdecl* TMxPluginPort_Track_SetLabelName)(int ScoreNumber, int TrackNumber, char* LabelName, int Reserved);
typedef int(_cdecl* TMxPluginPort_Track_FindTrackLabel)(int ScoreNumber, char* LabelName);

typedef BOOL(_cdecl* TMxPluginPort_TrackProperty_SetData)(int ScoreNumber, int TrackNumber, int IDNum, int Value);
typedef BOOL(_cdecl* TMxPluginPort_TrackProperty_GetData)(int ScoreNumber, int TrackNumber, int IDNum, void* Value);

typedef int(_cdecl* TMxPluginPort_LoopTrack_GetLength)(int ScoreNumbe);
typedef BOOL(_cdecl* TMxPluginPort_LoopTrack_GetValue)(int ScoreNumber, int FrameNumber, int* Value);
typedef BOOL(_cdecl* TMxPluginPort_LoopTrack_SetValue)(int ScoreNumber, int FrameNumber, int Value);
typedef BOOL(_cdecl* TMxPluginPort_LoopTrack_Trim)(int ScoreNumber);
typedef BOOL(_cdecl* TMxPluginPort_CastPropety_SetDataInt1)(int CastType, int CastNumber, int PropertyType, int Value);
typedef BOOL(_cdecl* TMxPluginPort_CastPropety_SetDataInt2)(int CastType, int CastNumber, int PropertyType, int	 Value1, int Value2);
typedef BOOL(_cdecl* TMxPluginPort_CastPropety_SetDataInt3)(int CastType, int CastNumber, int PropertyType, int	 Value1, int Value2, int Value3);
typedef BOOL(_cdecl* TMxPluginPort_CastPropety_SetDataPtr)(int CastType, int CastNumber, int PropertyType, void* Value);
typedef BOOL(_cdecl* TMxPluginPort_CastPropety_SetDataFloat)(int CastType, int CastNumber, int PropertyType, float Value);
typedef BOOL(_cdecl* TMxPluginPort_CastPropety_GetData)(int CastType, int CastNumber, int PropertyType, void* Value);
typedef BOOL(_cdecl* TMxPluginPort_Primitive_QuadPolygon)(int CastNumber, char* CastName, MXPLUGIN_VECTOR3D V1, MXPLUGIN_VECTOR3D V2, MXPLUGIN_VECTOR3D V3, MXPLUGIN_VECTOR3D V4);

typedef BOOL(_cdecl* TMxPluginPort_Project_SetPropertyInt)(int ID, int Value);
typedef BOOL(_cdecl* TMxPluginPort_Project_GetPropertyInt)(int ID, int* Value);

typedef BOOL(_cdecl* TMxPluginPort_Cast_Text_GetLineCount)(int CastNumber, int LangNum, int* Count);
typedef BOOL(_cdecl* TMxPluginPort_Cast_Text_GetLineString)(int CastNumber, int LineNumber, int LangNum, void** St);
typedef BOOL(_cdecl* TMxPluginPort_Cast_TextML_GetLangAssigned)(int CastNumber, int LangNum, BOOL* Result);
typedef BOOL(_cdecl* TMxPluginPort_Cast_TextML_CreateLanguage)(int CastNumber, int LangNum);
typedef BOOL(_cdecl* TMxPluginPort_Cast_TextML_RemoveLanguage)(int CastNumber, int LangNum);

//DLLの関数を定義
TMxPluginPort_System_AddMemu				subMxPluginPort_System_AddMemu = NULL;
TMxPluginPort_System_MenuEnabled			subMxPluginPort_System_MenuEnabled = NULL;
TMxPluginPort_System_MenuVisible			subMxPluginPort_System_MenuVisible = NULL;
TMxPluginPort_System_MenuCaption			subMxPluginPort_System_MenuCaption = NULL;

TMxPluginPort_System_Paint					subMxPluginPort_System_Paint = NULL;
TMxPluginPort_System_AttachEvent			subMxPluginPort_System_AttachEvent = NULL;
TMxPluginPort_System_GetHWnd				subMxPluginPort_System_GetHWnd = NULL;
TMxPluginPort_System_Progress				subMxPluginPort_System_Progress = NULL;
TMxPluginPort_System_ProgressMsg			subMxPluginPort_System_ProgressMsg = NULL;
TMxPluginPort_System_TrimLabelName			subMxPluginPort_System_TrimLabelName = NULL;
TMxPluginPort_System_GetSDKVersion			subMxPluginPort_System_GetSDKVersion = NULL;
TMxPluginPort_System_GetSDKLanguage			subMxPluginPort_System_GetSDKLanguage = NULL;
TMxPluginPort_System_ProcessMessages		subMxPluginPort_System_ProcessMessages = NULL;
TMxPluginPort_Event_GetUIHandle				subMxPluginPort_Event_GetUIHandle = NULL;
TMxPluginPort_Event_GetEventType			subMxPluginPort_Event_GetEventType = NULL;
TMxPluginPort_Event_GetPreEvent				subMxPluginPort_Event_GetPreEvent = NULL;
TMxPluginPort_Event_GetMXPFileName			subMxPluginPort_Event_GetMXPFileName = NULL;

TMxPluginPort_Event_Score_GetScoreTrack		subMxPluginPort_Event_Score_GetScoreTrack = NULL;
TMxPluginPort_Event_Score_GetSelectedCount	subMxPluginPort_Event_Score_GetSelectedCount = NULL;
TMxPluginPort_Event_Score_GetSelectedTrack	subMxPluginPort_Event_Score_GetSelectedTrack = NULL;

TMxPluginPort_Event_ScoreRename_GetNumber	subMxPluginPort_Event_ScoreRename_GetNumber = NULL;
TMxPluginPort_Event_ScoreRename_GetOldName	subMxPluginPort_Event_ScoreRename_GetOldName = NULL;
TMxPluginPort_Event_ScoreRename_GetNewName	subMxPluginPort_Event_ScoreRename_GetNewName = NULL;

TMxPluginPort_Event_Cast_GetCastType		subMxPluginPort_Event_Cast_GetCastType = NULL;
TMxPluginPort_Event_Cast_GetCastNumber		subMxPluginPort_Event_Cast_GetCastNumber = NULL;
TMxPluginPort_Event_Cast_GetOldName			subMxPluginPort_Event_Cast_GetOldName = NULL;
TMxPluginPort_Event_Cast_GetNewName			subMxPluginPort_Event_Cast_GetNewName = NULL;

TMxPluginPort_Project_Init					subMxPluginPort_Project_Init = NULL;
TMxPluginPort_Project_LoadCabinet			subMxPluginPort_Project_LoadCabinet = NULL;
TMxPluginPort_Project_LoadCabinetEx 		subMxPluginPort_Project_LoadCabinetEx = NULL;
TMxPluginPort_Project_SetScreenSize 		subMxPluginPort_Project_SetScreenSize = NULL;
TMxPluginPort_Project_GetContentsPath		subMxPluginPort_Project_GetContentsPath = NULL;
TMxPluginPort_Project_GetContentsName		subMxPluginPort_Project_GetContentsName = NULL;
TMxPluginPort_Project_GetContentsSaved		subMxPluginPort_Project_GetContentsSaved = NULL;
TMxPluginPort_Project_SaveContents			subMxPluginPort_Project_SaveContents = NULL;
TMxPluginPort_Project_LoadContents			subMxPluginPort_Project_LoadContents = NULL;
TMxPluginPort_Project_GetContentsChanged	subMxPluginPort_Project_GetContentsChanged = NULL;
TMxPluginPort_Project_SetContentsChanged	subMxPluginPort_Project_SetContentsChanged = NULL;
TMxPluginPort_Project_ClearContentsChanged	subMxPluginPort_Project_ClearContentsChanged = NULL;
TMxPluginPort_Project_CreateRuntimeFile		subMxPluginPort_Project_CreateRuntimeFile = NULL;
TMxPluginPort_Project_GetContentsRunning	subMxPluginPort_Project_GetContentsRunning = NULL;
TMxPluginPort_Project_LoadFile				subMxPluginPort_Project_LoadFile = NULL;

TMxPluginPort_CLang_GetEnabled				subMxPluginPort_CLang_GetEnabled = NULL;
TMxPluginPort_CLang_GetPathSRC				subMxPluginPort_CLang_GetPathSRC = NULL;
TMxPluginPort_CLang_GetPathEvent			subMxPluginPort_CLang_GetPathEvent = NULL;
TMxPluginPort_CLang_GetPathLib				subMxPluginPort_CLang_GetPathLib = NULL;
TMxPluginPort_CLang_GetPathOBJ				subMxPluginPort_CLang_GetPathOBJ = NULL;
TMxPluginPort_CLang_GetFileNameConst		subMxPluginPort_CLang_GetFileNameConst = NULL;
TMxPluginPort_CLang_GetFileNameEventSource	subMxPluginPort_CLang_GetFileNameEventSource = NULL;
TMxPluginPort_CLang_GetFileNameEventHeader	subMxPluginPort_CLang_GetFileNameEventHeader = NULL;

TMxPluginPort_CLang_GetInitEvent_Enabled    subMxPluginPort_CLang_GetInitEvent_Enabled = NULL;
TMxPluginPort_CLang_GetInitEvent_Type       subMxPluginPort_CLang_GetInitEvent_Type = NULL;
TMxPluginPort_CLang_GetInitEvent_Name       subMxPluginPort_CLang_GetInitEvent_Name = NULL;
TMxPluginPort_CLang_GetFinallyEvent_Enabled subMxPluginPort_CLang_GetFinallyEvent_Enabled = NULL;
TMxPluginPort_CLang_GetFinallyEvent_Type    subMxPluginPort_CLang_GetFinallyEvent_Type = NULL;
TMxPluginPort_CLang_GetFinallyEvent_Name    subMxPluginPort_CLang_GetFinallyEvent_Name = NULL;
TMxPluginPort_CLang_GetInitEventFuncName    subMxPluginPort_CLang_GetInitEventFuncName = NULL;
TMxPluginPort_CLang_GetFinallyEventFuncName	subMxPluginPort_CLang_GetFinallyEventFuncName = NULL;

TMxPluginPort_CLang_SetEnabled				subMxPluginPort_CLang_SetEnabled = NULL;
TMxPluginPort_CLang_SetPathSRCNative		subMxPluginPort_CLang_SetPathSRCNative = NULL;
TMxPluginPort_CLang_SetPathEventNative		subMxPluginPort_CLang_SetPathEventNative = NULL;
TMxPluginPort_CLang_SetPathLibNative		subMxPluginPort_CLang_SetPathLibNative = NULL;
TMxPluginPort_CLang_SetPathOBJNative		subMxPluginPort_CLang_SetPathOBJNative = NULL;
TMxPluginPort_CLang_GetPathSRCNative		subMxPluginPort_CLang_GetPathSRCNative = NULL;
TMxPluginPort_CLang_GetPathEventNative		subMxPluginPort_CLang_GetPathEventNative = NULL;
TMxPluginPort_CLang_GetPathLibNative		subMxPluginPort_CLang_GetPathLibNative = NULL;
TMxPluginPort_CLang_GetPathOBJNative		subMxPluginPort_CLang_GetPathOBJNative = NULL;

TMxPluginPort_CLang_SetInitEvent_Enabled    subMxPluginPort_CLang_SetInitEvent_Enabled = NULL;
TMxPluginPort_CLang_SetInitEvent_Type       subMxPluginPort_CLang_SetInitEvent_Type = NULL;
TMxPluginPort_CLang_SetInitEvent_Name       subMxPluginPort_CLang_SetInitEvent_Name = NULL;
TMxPluginPort_CLang_SetFinallyEvent_Enabled subMxPluginPort_CLang_SetFinallyEvent_Enabled = NULL;
TMxPluginPort_CLang_SetFinallyEvent_Type    subMxPluginPort_CLang_SetFinallyEvent_Type = NULL;
TMxPluginPort_CLang_SetFinallyEvent_Name    subMxPluginPort_CLang_SetFinallyEvent_Name = NULL;

TMxPluginPort_CLang_SetEventListName_Type	subMxPluginPort_CLang_SetEventListName_Type = NULL;
TMxPluginPort_CLang_SetEventListName_Name	subMxPluginPort_CLang_SetEventListName_Name = NULL;
TMxPluginPort_CLang_SetEventSymbolName_Type	subMxPluginPort_CLang_SetEventSymbolName_Type = NULL;
TMxPluginPort_CLang_SetEventSymbolName_Name	subMxPluginPort_CLang_SetEventSymbolName_Name = NULL;
TMxPluginPort_CLang_SetEventTableName_Type	subMxPluginPort_CLang_SetEventTableName_Type = NULL;
TMxPluginPort_CLang_SetEventTableName_Name	subMxPluginPort_CLang_SetEventTableName_Name = NULL;
TMxPluginPort_CLang_SetEventTableName_Alias	subMxPluginPort_CLang_SetEventTableName_Alias = NULL;

TMxPluginPort_Project_MultiLang_GetEnabled	subMxPluginPort_Project_MultiLang_GetEnabled = NULL;
TMxPluginPort_Project_MultiLang_SetEnabled	subMxPluginPort_Project_MultiLang_SetEnabled = NULL;
TMxPluginPort_Project_MultiLang_GetCount	subMxPluginPort_Project_MultiLang_GetCount = NULL;
TMxPluginPort_Project_MultiLang_GetName		subMxPluginPort_Project_MultiLang_GetName = NULL;
TMxPluginPort_Project_MultiLang_SetName		subMxPluginPort_Project_MultiLang_SetName = NULL;
TMxPluginPort_Project_MultiLang_Add			subMxPluginPort_Project_MultiLang_Add = NULL;
TMxPluginPort_Project_MultiLang_Remove		subMxPluginPort_Project_MultiLang_Remove = NULL;

TMxPluginPort_Cast_FindBlank				subMxPluginPort_Cast_FindBlank = NULL;
TMxPluginPort_Cast_FindBlankSince			subMxPluginPort_Cast_FindBlankSince = NULL;
TMxPluginPort_Cast_GetCastCount 			subMxPluginPort_Cast_GetCastCount = NULL;
TMxPluginPort_Cast_CreateCamera 			subMxPluginPort_Cast_CreateCamera = NULL;
TMxPluginPort_Cast_CreateLight				subMxPluginPort_Cast_CreateLight = NULL;
TMxPluginPort_Cast_Delete					subMxPluginPort_Cast_Delete = NULL;
TMxPluginPort_Cast_UseCheck 				subMxPluginPort_Cast_UseCheck = NULL;
TMxPluginPort_Cast_GetCastName				subMxPluginPort_Cast_GetCastName = NULL;
TMxPluginPort_Cast_SetCastName				subMxPluginPort_Cast_SetCastName = NULL;
TMxPluginPort_Cast_SaveToFile				subMxPluginPort_Cast_SaveToFile = NULL;
TMxPluginPort_Cast_FindCast					subMxPluginPort_Cast_FindCast = NULL;
TMxPluginPort_Cast_CreateWave				subMxPluginPort_Cast_CreateWave = NULL;
TMxPluginPort_Cast_CreateText				subMxPluginPort_Cast_CreateText = NULL;
TMxPluginPort_Cast_CreateScript 			subMxPluginPort_Cast_CreateScript = NULL;
TMxPluginPort_Cast_CreateScriptEx 			subMxPluginPort_Cast_CreateScriptEx = NULL;
TMxPluginPort_Cast_CreateTexture			subMxPluginPort_Cast_CreateTexture = NULL;
TMxPluginPort_Cast_CreateTextureEx			subMxPluginPort_Cast_CreateTextureEx = NULL;
TMxPluginPort_Cast_CreateBitmap				subMxPluginPort_Cast_CreateBitmap = NULL;
TMxPluginPort_Cast_Assigned					subMxPluginPort_Cast_Assigned = NULL;
TMxPluginPort_Cast_TrimCastName				subMxPluginPort_Cast_TrimCastName = NULL;
TMxPluginPort_Cast_TrimFileName				subMxPluginPort_Cast_TrimFileName = NULL;
TMxPluginPort_Cast_Exchange					subMxPluginPort_Cast_Exchange = NULL;

TMxPluginPort_Score_GetScoreName			subMxPluginPort_Score_GetScoreName = NULL;
TMxPluginPort_Score_GetScoreCount			subMxPluginPort_Score_GetScoreCount = NULL;
TMxPluginPort_Score_GetTrackCount			subMxPluginPort_Score_GetTrackCount = NULL;
TMxPluginPort_Score_CreateScore 			subMxPluginPort_Score_CreateScore = NULL;
TMxPluginPort_Score_CreateTrack 			subMxPluginPort_Score_CreateTrack = NULL;
TMxPluginPort_Score_DeleteTrack 			subMxPluginPort_Score_DeleteTrack = NULL;
TMxPluginPort_Score_Trim					subMxPluginPort_Score_Trim = NULL;
TMxPluginPort_Score_GetLength				subMxPluginPort_Score_GetLength = NULL;
TMxPluginPort_Score_Find					subMxPluginPort_Score_Find = NULL;
TMxPluginPort_Score_UpdateLength			subMxPluginPort_Score_UpdateLength = NULL;
TMxPluginPort_Score_Exchange				subMxPluginPort_Score_Exchange = NULL;
TMxPluginPort_Score_DeleteScore				subMxPluginPort_Score_DeleteScore = NULL;
TMxPluginPort_Score_GetLabelName			subMxPluginPort_Score_GetLabelName = NULL;
TMxPluginPort_Score_SetLabelName			subMxPluginPort_Score_SetLabelName = NULL;
TMxPluginPort_Score_GetLabelPosMax			subMxPluginPort_Score_GetLabelPosMax = NULL;
TMxPluginPort_Score_FindFrameLabel			subMxPluginPort_Score_FindFrameLabel = NULL;
TMxPluginPort_Score_Clear					subMxPluginPort_Score_Clear = NULL;
TMxPluginPort_Score_MoveTrack				subMxPluginPort_Score_MoveTrack = NULL;

TMxPluginPort_Score_SetAnnotationEncode		subMxPluginPort_Score_SetAnnotationEncode = NULL;
TMxPluginPort_Score_SetAnnotationData		subMxPluginPort_Score_SetAnnotationData = NULL;
TMxPluginPort_Score_GetAnnotationEncode		subMxPluginPort_Score_GetAnnotationEncode = NULL;
TMxPluginPort_Score_GetAnnotationData		subMxPluginPort_Score_GetAnnotationData = NULL;
TMxPluginPort_Score_GetAnnotationCount		subMxPluginPort_Score_GetAnnotationCount = NULL;
TMxPluginPort_Score_ClearAnnotation			subMxPluginPort_Score_ClearAnnotation = NULL;
TMxPluginPort_Score_InsertAnnotationData	subMxPluginPort_Score_InsertAnnotationData = NULL;
TMxPluginPort_Score_RemoveAnnotationData	subMxPluginPort_Score_RemoveAnnotationData = NULL;

TMxPluginPort_Track_GetCastType 			subMxPluginPort_Track_GetCastType = NULL;
TMxPluginPort_Track_GetCastNumber			subMxPluginPort_Track_GetCastNumber = NULL;
TMxPluginPort_Track_SetCastNumber			subMxPluginPort_Track_SetCastNumber = NULL;
TMxPluginPort_Track_GetLength				subMxPluginPort_Track_GetLength = NULL;
TMxPluginPort_Track_GetParent				subMxPluginPort_Track_GetParent = NULL;
TMxPluginPort_Track_TestSetParent			subMxPluginPort_Track_TestSetParent = NULL;
TMxPluginPort_Track_SetParent				subMxPluginPort_Track_SetParent = NULL;
TMxPluginPort_Track_GetFrameData			subMxPluginPort_Track_GetFrameData = NULL;
TMxPluginPort_Track_SetFrameData			subMxPluginPort_Track_SetFrameData = NULL;
TMxPluginPort_Track_Trim					subMxPluginPort_Track_Trim = NULL;
TMxPluginPort_Track_Assigned				subMxPluginPort_Track_Assigned = NULL;
TMxPluginPort_Track_FindBlank				subMxPluginPort_Track_FindBlank = NULL;
TMxPluginPort_Track_SetAttribute			subMxPluginPort_Track_SetAttribute = NULL;
TMxPluginPort_Track_GetAttribute			subMxPluginPort_Track_GetAttribute = NULL;
TMxPluginPort_Track_GetLabelName			subMxPluginPort_Track_GetLabelName = NULL;
TMxPluginPort_Track_SetLabelName			subMxPluginPort_Track_SetLabelName = NULL;
TMxPluginPort_Track_FindTrackLabel			subMxPluginPort_Track_FindTrackLabel = NULL;

TMxPluginPort_TrackProperty_SetData			subMxPluginPort_TrackProperty_SetData = NULL;
TMxPluginPort_TrackProperty_GetData			subMxPluginPort_TrackProperty_GetData = NULL;

TMxPluginPort_LoopTrack_GetLength			subMxPluginPort_LoopTrack_GetLength = NULL;
TMxPluginPort_LoopTrack_GetValue			subMxPluginPort_LoopTrack_GetValue = NULL;
TMxPluginPort_LoopTrack_SetValue			subMxPluginPort_LoopTrack_SetValue = NULL;
TMxPluginPort_LoopTrack_Trim				subMxPluginPort_LoopTrack_Trim = NULL;

TMxPluginPort_CastPropety_SetDataInt1		subMxPluginPort_CastPropety_SetDataInt1 = NULL;
TMxPluginPort_CastPropety_SetDataInt2		subMxPluginPort_CastPropety_SetDataInt2 = NULL;
TMxPluginPort_CastPropety_SetDataInt3		subMxPluginPort_CastPropety_SetDataInt3 = NULL;
TMxPluginPort_CastPropety_SetDataPtr		subMxPluginPort_CastPropety_SetDataPtr = NULL;
TMxPluginPort_CastPropety_SetDataFloat		subMxPluginPort_CastPropety_SetDataFloat = NULL;

TMxPluginPort_CastPropety_GetData			subMxPluginPort_CastPropety_GetData = NULL;
TMxPluginPort_Primitive_QuadPolygon			subMxPluginPort_Primitive_QuadPolygon = NULL;

TMxPluginPort_Project_SetPropertyInt		subMxPluginPort_Project_SetPropertyInt = NULL;
TMxPluginPort_Project_GetPropertyInt		subMxPluginPort_Project_GetPropertyInt = NULL;

TMxPluginPort_Cast_Text_GetLineCount		subMxPluginPort_Cast_Text_GetLineCount = NULL;
TMxPluginPort_Cast_Text_GetLineString		subMxPluginPort_Cast_Text_GetLineString = NULL;

TMxPluginPort_Cast_TextML_GetLangAssigned	subMxPluginPort_Cast_TextML_GetLangAssigned = NULL;
TMxPluginPort_Cast_TextML_CreateLanguage	subMxPluginPort_Cast_TextML_CreateLanguage = NULL;
TMxPluginPort_Cast_TextML_RemoveLanguage	subMxPluginPort_Cast_TextML_RemoveLanguage = NULL;

BOOL MxPlugin_SetProcAddress(int ID, void* FuncAddr)
{
	switch (ID)
	{
	case	IDMxPluginPort_System_Version: { if (FuncAddr < (void*)IC_Port_System_Version) return FALSE;											   break; }
	case	IDMxPluginPort_System_AddMemu: { subMxPluginPort_System_AddMemu = (TMxPluginPort_System_AddMemu)FuncAddr; break; }
	case	IDMxPluginPort_System_MenuEnabled: { subMxPluginPort_System_MenuEnabled = (TMxPluginPort_System_MenuEnabled)FuncAddr; break; }
	case	IDMxPluginPort_System_MenuVisible: { subMxPluginPort_System_MenuVisible = (TMxPluginPort_System_MenuVisible)FuncAddr; break; }
	case	IDMxPluginPort_System_MenuCaption: { subMxPluginPort_System_MenuCaption = (TMxPluginPort_System_MenuCaption)FuncAddr; break; }
	case	IDMxPluginPort_System_Paint: { subMxPluginPort_System_Paint = (TMxPluginPort_System_Paint)FuncAddr; break; }
	case	IDMxPluginPort_System_AttachEvent: { subMxPluginPort_System_AttachEvent = (TMxPluginPort_System_AttachEvent)FuncAddr; break; }
	case	IDMxPluginPort_System_GetHWnd: { subMxPluginPort_System_GetHWnd = (TMxPluginPort_System_GetHWnd)FuncAddr; break; }
	case	IDMxPluginPort_System_Progress: { subMxPluginPort_System_Progress = (TMxPluginPort_System_Progress)FuncAddr;
		subMxPluginPort_System_ProgressMsg = (TMxPluginPort_System_ProgressMsg)FuncAddr; break; }
	case	IDMxPluginPort_System_TrimLabelName: { subMxPluginPort_System_TrimLabelName = (TMxPluginPort_System_TrimLabelName)FuncAddr; break; }
	case	IDMxPluginPort_System_GetSDKVersion: { subMxPluginPort_System_GetSDKVersion = (TMxPluginPort_System_GetSDKVersion)FuncAddr; break; }
	case	IDMxPluginPort_System_GetSDKLanguage: { subMxPluginPort_System_GetSDKLanguage = (TMxPluginPort_System_GetSDKLanguage)FuncAddr; break; }
	case	IDMxPluginPort_System_ProcessMessages: { subMxPluginPort_System_ProcessMessages = (TMxPluginPort_System_ProcessMessages)FuncAddr; break; }
	case	IDMxPluginPort_Event_GetUIHandle: { subMxPluginPort_Event_GetUIHandle = (TMxPluginPort_Event_GetUIHandle)FuncAddr; break; }
	case	IDMxPluginPort_Event_GetEventType: { subMxPluginPort_Event_GetEventType = (TMxPluginPort_Event_GetEventType)FuncAddr; break; }
	case	IDMxPluginPort_Event_GetPreEvent: { subMxPluginPort_Event_GetPreEvent = (TMxPluginPort_Event_GetPreEvent)FuncAddr; break; }
	case	IDMxPluginPort_Event_GetMXPFileName: { subMxPluginPort_Event_GetMXPFileName = (TMxPluginPort_Event_GetMXPFileName)FuncAddr; break; }

	case	IDMxPluginPort_Event_Score_GetScoreTrack: { subMxPluginPort_Event_Score_GetScoreTrack = (TMxPluginPort_Event_Score_GetScoreTrack)FuncAddr; break; }
	case	IDMxPluginPort_Event_Score_GetSelectedCount: { subMxPluginPort_Event_Score_GetSelectedCount = (TMxPluginPort_Event_Score_GetSelectedCount)FuncAddr; break; }
	case	IDMxPluginPort_Event_Score_GetSelectedTrack: { subMxPluginPort_Event_Score_GetSelectedTrack = (TMxPluginPort_Event_Score_GetSelectedTrack)FuncAddr; break; }

	case	IDMxPluginPort_Event_ScoreRename_GetNumber: { subMxPluginPort_Event_ScoreRename_GetNumber = (TMxPluginPort_Event_ScoreRename_GetNumber)FuncAddr; break; }
	case	IDMxPluginPort_Event_ScoreRename_GetOldName: { subMxPluginPort_Event_ScoreRename_GetOldName = (TMxPluginPort_Event_ScoreRename_GetOldName)FuncAddr; break; }
	case	IDMxPluginPort_Event_ScoreRename_GetNewName: { subMxPluginPort_Event_ScoreRename_GetNewName = (TMxPluginPort_Event_ScoreRename_GetNewName)FuncAddr; break; }

	case	IDMxPluginPort_Event_Cast_GetCastType: { subMxPluginPort_Event_Cast_GetCastType = (TMxPluginPort_Event_Cast_GetCastType)FuncAddr; break; }
	case	IDMxPluginPort_Event_Cast_GetCastNumber: { subMxPluginPort_Event_Cast_GetCastNumber = (TMxPluginPort_Event_Cast_GetCastNumber)FuncAddr; break; }
	case	IDMxPluginPort_Event_Cast_GetOldName: { subMxPluginPort_Event_Cast_GetOldName = (TMxPluginPort_Event_Cast_GetOldName)FuncAddr; break; }
	case	IDMxPluginPort_Event_Cast_GetNewName: { subMxPluginPort_Event_Cast_GetNewName = (TMxPluginPort_Event_Cast_GetNewName)FuncAddr; break; }

	case	IDMxPluginPort_Project_Init: { subMxPluginPort_Project_Init = (TMxPluginPort_Project_Init)FuncAddr; break; }
	case	IDMxPluginPort_Project_LoadCabinet: { subMxPluginPort_Project_LoadCabinet = (TMxPluginPort_Project_LoadCabinet)FuncAddr; break; }
	case	IDMxPluginPort_Project_LoadCabinetEx: { subMxPluginPort_Project_LoadCabinetEx = (TMxPluginPort_Project_LoadCabinetEx)FuncAddr; break; }
	case	IDMxPluginPort_Project_SetScreenSize: { subMxPluginPort_Project_SetScreenSize = (TMxPluginPort_Project_SetScreenSize)FuncAddr; break; }
	case	IDMxPluginPort_Project_GetContentsPath: { subMxPluginPort_Project_GetContentsPath = (TMxPluginPort_Project_GetContentsPath)FuncAddr; break; }
	case	IDMxPluginPort_Project_GetContentsName: { subMxPluginPort_Project_GetContentsName = (TMxPluginPort_Project_GetContentsName)FuncAddr; break; }
	case	IDMxPluginPort_Project_GetContentsSaved: { subMxPluginPort_Project_GetContentsSaved = (TMxPluginPort_Project_GetContentsSaved)FuncAddr; break; }
	case	IDMxPluginPort_Project_SaveContents: { subMxPluginPort_Project_SaveContents = (TMxPluginPort_Project_SaveContents)FuncAddr; break; }
	case	IDMxPluginPort_Project_LoadContents: { subMxPluginPort_Project_LoadContents = (TMxPluginPort_Project_LoadContents)FuncAddr; break; }
	case	IDMxPluginPort_Project_GetContentsChanged: { subMxPluginPort_Project_GetContentsChanged = (TMxPluginPort_Project_GetContentsChanged)FuncAddr; break; }
	case	IDMxPluginPort_Project_SetContentsChanged: { subMxPluginPort_Project_SetContentsChanged = (TMxPluginPort_Project_SetContentsChanged)FuncAddr; break; }
	case	IDMxPluginPort_Project_ClearContentsChanged: { subMxPluginPort_Project_ClearContentsChanged = (TMxPluginPort_Project_ClearContentsChanged)FuncAddr; break; }
	case	IDMxPluginPort_Project_CreateRuntimeFile: { subMxPluginPort_Project_CreateRuntimeFile = (TMxPluginPort_Project_CreateRuntimeFile)FuncAddr; break; }
	case	IDMxPluginPort_Project_GetContentsRunning: { subMxPluginPort_Project_GetContentsRunning = (TMxPluginPort_Project_GetContentsRunning)FuncAddr; break; }
	case	IDMxPluginPort_Project_LoadFile: { subMxPluginPort_Project_LoadFile = (TMxPluginPort_Project_LoadFile)FuncAddr; break; }

	case	IDMxPluginPort_CLang_GetEnabled: { subMxPluginPort_CLang_GetEnabled = (TMxPluginPort_CLang_GetEnabled)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetPathSRC: { subMxPluginPort_CLang_GetPathSRC = (TMxPluginPort_CLang_GetPathSRC)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetPathEvent: { subMxPluginPort_CLang_GetPathEvent = (TMxPluginPort_CLang_GetPathEvent)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetPathLib: { subMxPluginPort_CLang_GetPathLib = (TMxPluginPort_CLang_GetPathLib)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetPathOBJ: { subMxPluginPort_CLang_GetPathOBJ = (TMxPluginPort_CLang_GetPathOBJ)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetFileNameConst: { subMxPluginPort_CLang_GetFileNameConst = (TMxPluginPort_CLang_GetFileNameConst)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetFileNameEventSource: { subMxPluginPort_CLang_GetFileNameEventSource = (TMxPluginPort_CLang_GetFileNameEventSource)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetFileNameEventHeader: { subMxPluginPort_CLang_GetFileNameEventHeader = (TMxPluginPort_CLang_GetFileNameEventHeader)FuncAddr; break; }

	case	IDMxPluginPort_CLang_GetInitEvent_Enabled: { subMxPluginPort_CLang_GetInitEvent_Enabled = (TMxPluginPort_CLang_GetInitEvent_Enabled)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetInitEvent_Type: { subMxPluginPort_CLang_GetInitEvent_Type = (TMxPluginPort_CLang_GetInitEvent_Type)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetInitEvent_Name: { subMxPluginPort_CLang_GetInitEvent_Name = (TMxPluginPort_CLang_GetInitEvent_Name)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetFinallyEvent_Enabled: { subMxPluginPort_CLang_GetFinallyEvent_Enabled = (TMxPluginPort_CLang_GetFinallyEvent_Enabled)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetFinallyEvent_Type: { subMxPluginPort_CLang_GetFinallyEvent_Type = (TMxPluginPort_CLang_GetFinallyEvent_Type)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetFinallyEvent_Name: { subMxPluginPort_CLang_GetFinallyEvent_Name = (TMxPluginPort_CLang_GetFinallyEvent_Name)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetInitEventFuncName: { subMxPluginPort_CLang_GetInitEventFuncName = (TMxPluginPort_CLang_GetInitEventFuncName)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetFinallyEventFuncName: { subMxPluginPort_CLang_GetFinallyEventFuncName = (TMxPluginPort_CLang_GetFinallyEventFuncName)FuncAddr; break; }

	case	IDMxPluginPort_CLang_SetEnabled: { subMxPluginPort_CLang_SetEnabled = (TMxPluginPort_CLang_SetEnabled)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetPathSRCNative: { subMxPluginPort_CLang_SetPathSRCNative = (TMxPluginPort_CLang_SetPathSRCNative)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetPathEventNative: { subMxPluginPort_CLang_SetPathEventNative = (TMxPluginPort_CLang_SetPathEventNative)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetPathLibNative: { subMxPluginPort_CLang_SetPathLibNative = (TMxPluginPort_CLang_SetPathLibNative)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetPathOBJNative: { subMxPluginPort_CLang_SetPathOBJNative = (TMxPluginPort_CLang_SetPathOBJNative)FuncAddr; break; }

	case	IDMxPluginPort_CLang_GetPathSRCNative: { subMxPluginPort_CLang_GetPathSRCNative = (TMxPluginPort_CLang_GetPathSRCNative)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetPathEventNative: { subMxPluginPort_CLang_GetPathEventNative = (TMxPluginPort_CLang_GetPathEventNative)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetPathLibNative: { subMxPluginPort_CLang_GetPathLibNative = (TMxPluginPort_CLang_GetPathLibNative)FuncAddr; break; }
	case	IDMxPluginPort_CLang_GetPathOBJNative: { subMxPluginPort_CLang_GetPathOBJNative = (TMxPluginPort_CLang_GetPathOBJNative)FuncAddr; break; }

	case	IDMxPluginPort_CLang_SetInitEvent_Enabled: { subMxPluginPort_CLang_SetInitEvent_Enabled = (TMxPluginPort_CLang_SetInitEvent_Enabled)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetInitEvent_Type: { subMxPluginPort_CLang_SetInitEvent_Type = (TMxPluginPort_CLang_SetInitEvent_Type)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetInitEvent_Name: { subMxPluginPort_CLang_SetInitEvent_Name = (TMxPluginPort_CLang_SetInitEvent_Name)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetFinallyEvent_Enabled: { subMxPluginPort_CLang_SetFinallyEvent_Enabled = (TMxPluginPort_CLang_SetFinallyEvent_Enabled)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetFinallyEvent_Type: { subMxPluginPort_CLang_SetFinallyEvent_Type = (TMxPluginPort_CLang_SetFinallyEvent_Type)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetFinallyEvent_Name: { subMxPluginPort_CLang_SetFinallyEvent_Name = (TMxPluginPort_CLang_SetFinallyEvent_Name)FuncAddr; break; }

	case	IDMxPluginPort_CLang_SetEventListName_Type: { subMxPluginPort_CLang_SetEventListName_Type = (TMxPluginPort_CLang_SetEventListName_Type)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetEventListName_Name: { subMxPluginPort_CLang_SetEventListName_Name = (TMxPluginPort_CLang_SetEventListName_Name)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetEventSymbolName_Type: { subMxPluginPort_CLang_SetEventSymbolName_Type = (TMxPluginPort_CLang_SetEventSymbolName_Type)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetEventSymbolName_Name: { subMxPluginPort_CLang_SetEventSymbolName_Name = (TMxPluginPort_CLang_SetEventSymbolName_Name)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetEventTableName_Type: { subMxPluginPort_CLang_SetEventTableName_Type = (TMxPluginPort_CLang_SetEventTableName_Type)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetEventTableName_Name: { subMxPluginPort_CLang_SetEventTableName_Name = (TMxPluginPort_CLang_SetEventTableName_Name)FuncAddr; break; }
	case	IDMxPluginPort_CLang_SetEventTableName_Alias: { subMxPluginPort_CLang_SetEventTableName_Alias = (TMxPluginPort_CLang_SetEventTableName_Alias)FuncAddr; break; }

	case	IDMxPluginPort_Project_MultiLang_GetEnabled: { subMxPluginPort_Project_MultiLang_GetEnabled = (TMxPluginPort_Project_MultiLang_GetEnabled)FuncAddr; break; }
	case	IDMxPluginPort_Project_MultiLang_SetEnabled: { subMxPluginPort_Project_MultiLang_SetEnabled = (TMxPluginPort_Project_MultiLang_SetEnabled)FuncAddr; break; }
	case	IDMxPluginPort_Project_MultiLang_GetCount: { subMxPluginPort_Project_MultiLang_GetCount = (TMxPluginPort_Project_MultiLang_GetCount)FuncAddr; break; }
	case	IDMxPluginPort_Project_MultiLang_GetName: { subMxPluginPort_Project_MultiLang_GetName = (TMxPluginPort_Project_MultiLang_GetName)FuncAddr; break; }
	case	IDMxPluginPort_Project_MultiLang_SetName: { subMxPluginPort_Project_MultiLang_SetName = (TMxPluginPort_Project_MultiLang_SetName)FuncAddr; break; }
	case	IDMxPluginPort_Project_MultiLang_Add: { subMxPluginPort_Project_MultiLang_Add = (TMxPluginPort_Project_MultiLang_Add)FuncAddr; break; }
	case	IDMxPluginPort_Project_MultiLang_Remove: { subMxPluginPort_Project_MultiLang_Remove = (TMxPluginPort_Project_MultiLang_Remove)FuncAddr; break; }

	case	IDMxPluginPort_Cast_FindBlank: { subMxPluginPort_Cast_FindBlank = (TMxPluginPort_Cast_FindBlank)FuncAddr; break; }
	case	IDMxPluginPort_Cast_FindBlankSince: { subMxPluginPort_Cast_FindBlankSince = (TMxPluginPort_Cast_FindBlankSince)FuncAddr; break; }
	case	IDMxPluginPort_Cast_GetCastCount: { subMxPluginPort_Cast_GetCastCount = (TMxPluginPort_Cast_GetCastCount)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateCamera: { subMxPluginPort_Cast_CreateCamera = (TMxPluginPort_Cast_CreateCamera)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateLight: { subMxPluginPort_Cast_CreateLight = (TMxPluginPort_Cast_CreateLight)FuncAddr; break; }
	case	IDMxPluginPort_Cast_Delete: { subMxPluginPort_Cast_Delete = (TMxPluginPort_Cast_Delete)FuncAddr; break; }
	case	IDMxPluginPort_Cast_UseCheck: { subMxPluginPort_Cast_UseCheck = (TMxPluginPort_Cast_UseCheck)FuncAddr; break; }
	case	IDMxPluginPort_Cast_GetCastName: { subMxPluginPort_Cast_GetCastName = (TMxPluginPort_Cast_GetCastName)FuncAddr; break; }
	case	IDMxPluginPort_Cast_SetCastName: { subMxPluginPort_Cast_SetCastName = (TMxPluginPort_Cast_SetCastName)FuncAddr; break; }
	case	IDMxPluginPort_Cast_SaveToFile: { subMxPluginPort_Cast_SaveToFile = (TMxPluginPort_Cast_SaveToFile)FuncAddr; break; }
	case	IDMxPluginPort_Cast_FindCast: { subMxPluginPort_Cast_FindCast = (TMxPluginPort_Cast_FindCast)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateWave: { subMxPluginPort_Cast_CreateWave = (TMxPluginPort_Cast_CreateWave)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateText: { subMxPluginPort_Cast_CreateText = (TMxPluginPort_Cast_CreateText)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateScript: { subMxPluginPort_Cast_CreateScript = (TMxPluginPort_Cast_CreateScript)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateScriptEx: { subMxPluginPort_Cast_CreateScriptEx = (TMxPluginPort_Cast_CreateScriptEx)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateTexture: { subMxPluginPort_Cast_CreateTexture = (TMxPluginPort_Cast_CreateTexture)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateTextureEx: { subMxPluginPort_Cast_CreateTextureEx = (TMxPluginPort_Cast_CreateTextureEx)FuncAddr; break; }
	case	IDMxPluginPort_Cast_CreateBitmap: { subMxPluginPort_Cast_CreateBitmap = (TMxPluginPort_Cast_CreateBitmap)FuncAddr; break; }
	case	IDMxPluginPort_Cast_Assigned: { subMxPluginPort_Cast_Assigned = (TMxPluginPort_Cast_Assigned)FuncAddr; break; }
	case	IDMxPluginPort_Cast_TrimCastName: { subMxPluginPort_Cast_TrimCastName = (TMxPluginPort_Cast_TrimCastName)FuncAddr; break; }
	case	IDMxPluginPort_Cast_TrimFileName: { subMxPluginPort_Cast_TrimFileName = (TMxPluginPort_Cast_TrimFileName)FuncAddr; break; }
	case	IDMxPluginPort_Cast_Exchange: { subMxPluginPort_Cast_Exchange = (TMxPluginPort_Cast_Exchange)FuncAddr; break; }

	case	IDMxPluginPort_Score_GetScoreName: { subMxPluginPort_Score_GetScoreName = (TMxPluginPort_Score_GetScoreName)FuncAddr; break; }
	case	IDMxPluginPort_Score_GetScoreCount: { subMxPluginPort_Score_GetScoreCount = (TMxPluginPort_Score_GetScoreCount)FuncAddr; break; }
	case	IDMxPluginPort_Score_GetTrackCount: { subMxPluginPort_Score_GetTrackCount = (TMxPluginPort_Score_GetTrackCount)FuncAddr; break; }
	case	IDMxPluginPort_Score_CreateScore: { subMxPluginPort_Score_CreateScore = (TMxPluginPort_Score_CreateScore)FuncAddr; break; }
	case	IDMxPluginPort_Score_CreateTrack: { subMxPluginPort_Score_CreateTrack = (TMxPluginPort_Score_CreateTrack)FuncAddr; break; }

	case	IDMxPluginPort_Track_GetCastType: { subMxPluginPort_Track_GetCastType = (TMxPluginPort_Track_GetCastType)FuncAddr; break; }
	case	IDMxPluginPort_Track_GetCastNumber: { subMxPluginPort_Track_GetCastNumber = (TMxPluginPort_Track_GetCastNumber)FuncAddr; break; }
	case	IDMxPluginPort_Track_SetCastNumber: { subMxPluginPort_Track_SetCastNumber = (TMxPluginPort_Track_SetCastNumber)FuncAddr; break; }

	case	IDMxPluginPort_Score_DeleteTrack: { subMxPluginPort_Score_DeleteTrack = (TMxPluginPort_Score_DeleteTrack)FuncAddr; break; }
	case	IDMxPluginPort_Score_Trim: { subMxPluginPort_Score_Trim = (TMxPluginPort_Score_Trim)FuncAddr; break; }
	case	IDMxPluginPort_Score_GetLength: { subMxPluginPort_Score_GetLength = (TMxPluginPort_Score_GetLength)FuncAddr; break; }
	case	IDMxPluginPort_Score_Find: { subMxPluginPort_Score_Find = (TMxPluginPort_Score_Find)FuncAddr; break; }
	case	IDMxPluginPort_Score_UpdatdeLength: { subMxPluginPort_Score_UpdateLength = (TMxPluginPort_Score_UpdateLength)FuncAddr; break; }
	case	IDMxPluginPort_Score_Exchange: { subMxPluginPort_Score_Exchange = (TMxPluginPort_Score_Exchange)FuncAddr; break; }
	case	IDMxPluginPort_Score_DeleteScore: { subMxPluginPort_Score_DeleteScore = (TMxPluginPort_Score_DeleteScore)FuncAddr; break; }
	case	IDMxPluginPort_Score_GetLabel: { subMxPluginPort_Score_GetLabelName = (TMxPluginPort_Score_GetLabelName)FuncAddr; break; }
	case	IDMxPluginPort_Score_SetLabel: { subMxPluginPort_Score_SetLabelName = (TMxPluginPort_Score_SetLabelName)FuncAddr; break; }
	case	IDMxPluginPort_Score_GetLabelPosMax: { subMxPluginPort_Score_GetLabelPosMax = (TMxPluginPort_Score_GetLabelPosMax)FuncAddr; break; }
	case	IDMxPluginPort_Score_FindFrameLabel: { subMxPluginPort_Score_FindFrameLabel = (TMxPluginPort_Score_FindFrameLabel)FuncAddr; break; }
	case	IDMxPluginPort_Score_Clear: { subMxPluginPort_Score_Clear = (TMxPluginPort_Score_Clear)FuncAddr; break; }
	case	IDMxPluginPort_Score_MoveTrack: { subMxPluginPort_Score_MoveTrack = (TMxPluginPort_Score_MoveTrack)FuncAddr; break; }

	case	IDMxPluginPort_Score_SetAnnotationEncode: { subMxPluginPort_Score_SetAnnotationEncode = (TMxPluginPort_Score_SetAnnotationEncode)FuncAddr; break; }
	case	IDMxPluginPort_Score_SetAnnotationData: { subMxPluginPort_Score_SetAnnotationData = (TMxPluginPort_Score_SetAnnotationData)FuncAddr; break; }
	case	IDMxPluginPort_Score_GetAnnotationEncode: { subMxPluginPort_Score_GetAnnotationEncode = (TMxPluginPort_Score_GetAnnotationEncode)FuncAddr; break; }
	case	IDMxPluginPort_Score_GetAnnotationData: { subMxPluginPort_Score_GetAnnotationData = (TMxPluginPort_Score_GetAnnotationData)FuncAddr; break; }
	case	IDMxPluginPort_Score_GetAnnotationCount: { subMxPluginPort_Score_GetAnnotationCount = (TMxPluginPort_Score_GetAnnotationCount)FuncAddr; break; }
	case	IDMxPluginPort_Score_ClearAnnotation: { subMxPluginPort_Score_ClearAnnotation = (TMxPluginPort_Score_ClearAnnotation)FuncAddr; break; }
	case	IDMxPluginPort_Score_InsertAnnotationData: { subMxPluginPort_Score_InsertAnnotationData = (TMxPluginPort_Score_InsertAnnotationData)FuncAddr; break; }
	case	IDMxPluginPort_Score_RemoveAnnotationData: { subMxPluginPort_Score_RemoveAnnotationData = (TMxPluginPort_Score_RemoveAnnotationData)FuncAddr; break; }

	case	IDMxPluginPort_Track_GetLength: { subMxPluginPort_Track_GetLength = (TMxPluginPort_Track_GetLength)FuncAddr; break; }
	case	IDMxPluginPort_Track_GetParent: { subMxPluginPort_Track_GetParent = (TMxPluginPort_Track_GetParent)FuncAddr; break; }
	case	IDMxPluginPort_Track_TestSetParent: { subMxPluginPort_Track_TestSetParent = (TMxPluginPort_Track_TestSetParent)FuncAddr; break; }
	case	IDMxPluginPort_Track_SetParent: { subMxPluginPort_Track_SetParent = (TMxPluginPort_Track_SetParent)FuncAddr; break; }
	case	IDMxPluginPort_Track_GetFrameData: { subMxPluginPort_Track_GetFrameData = (TMxPluginPort_Track_GetFrameData)FuncAddr; break; }
	case	IDMxPluginPort_Track_SetFrameData: { subMxPluginPort_Track_SetFrameData = (TMxPluginPort_Track_SetFrameData)FuncAddr; break; }
	case	IDMxPluginPort_Track_Trim: { subMxPluginPort_Track_Trim = (TMxPluginPort_Track_Trim)FuncAddr; break; }
	case	IDMxPluginPort_Track_Assigned: { subMxPluginPort_Track_Assigned = (TMxPluginPort_Track_Assigned)FuncAddr; break; }
	case	IDMxPluginPort_Track_FindBlank: { subMxPluginPort_Track_FindBlank = (TMxPluginPort_Track_FindBlank)FuncAddr; break; }
	case	IDMxPluginPort_Track_SetAttribute: { subMxPluginPort_Track_SetAttribute = (TMxPluginPort_Track_SetAttribute)FuncAddr; break; }
	case	IDMxPluginPort_Track_GetAttribute: { subMxPluginPort_Track_GetAttribute = (TMxPluginPort_Track_GetAttribute)FuncAddr; break; }
	case	IDMxPluginPort_Track_GetLabelName: { subMxPluginPort_Track_GetLabelName = (TMxPluginPort_Track_GetLabelName)FuncAddr; break; }
	case	IDMxPluginPort_Track_SetLabelName: { subMxPluginPort_Track_SetLabelName = (TMxPluginPort_Track_SetLabelName)FuncAddr; break; }
	case	IDMxPluginPort_Track_FindTrackLabel: { subMxPluginPort_Track_FindTrackLabel = (TMxPluginPort_Track_FindTrackLabel)FuncAddr; break; }

	case	IDMxPluginPort_TrackProperty_SetData: { subMxPluginPort_TrackProperty_SetData = (TMxPluginPort_TrackProperty_SetData)FuncAddr; break; }
	case	IDMxPluginPort_TrackProperty_GetData: { subMxPluginPort_TrackProperty_GetData = (TMxPluginPort_TrackProperty_GetData)FuncAddr; break; }

	case	IDMxPluginPort_LoopTrack_GetLength: { subMxPluginPort_LoopTrack_GetLength = (TMxPluginPort_LoopTrack_GetLength)FuncAddr; break; }
	case	IDMxPluginPort_LoopTrack_GetValue: { subMxPluginPort_LoopTrack_GetValue = (TMxPluginPort_LoopTrack_GetValue)FuncAddr; break; }
	case	IDMxPluginPort_LoopTrack_SetValue: { subMxPluginPort_LoopTrack_SetValue = (TMxPluginPort_LoopTrack_SetValue)FuncAddr; break; }
	case	IDMxPluginPort_LoopTrack_Trim: { subMxPluginPort_LoopTrack_Trim = (TMxPluginPort_LoopTrack_Trim)FuncAddr; break; }

	case	IDMxPluginPort_CastPropety_SetData: { subMxPluginPort_CastPropety_SetDataInt1 = (TMxPluginPort_CastPropety_SetDataInt1)FuncAddr;
		subMxPluginPort_CastPropety_SetDataPtr = (TMxPluginPort_CastPropety_SetDataPtr)FuncAddr;
		subMxPluginPort_CastPropety_SetDataFloat = (TMxPluginPort_CastPropety_SetDataFloat)FuncAddr; break; }
	case	IDMxPluginPort_CastPropety_SetData2: { subMxPluginPort_CastPropety_SetDataInt2 = (TMxPluginPort_CastPropety_SetDataInt2)FuncAddr; break; }
	case	IDMxPluginPort_CastPropety_SetData3: { subMxPluginPort_CastPropety_SetDataInt3 = (TMxPluginPort_CastPropety_SetDataInt3)FuncAddr; break; }
	case	IDMxPluginPort_CastPropety_GetData: { subMxPluginPort_CastPropety_GetData = (TMxPluginPort_CastPropety_GetData)FuncAddr; break; }

	case	IDMxPluginPort_Primitive_QuadPolygon: { subMxPluginPort_Primitive_QuadPolygon = (TMxPluginPort_Primitive_QuadPolygon)FuncAddr; break; }
	case	IDMxPluginPort_Project_SetPropertyInt: { subMxPluginPort_Project_SetPropertyInt = (TMxPluginPort_Project_SetPropertyInt)FuncAddr; break; }
	case	IDMxPluginPort_Project_GetPropertyInt: { subMxPluginPort_Project_GetPropertyInt = (TMxPluginPort_Project_GetPropertyInt)FuncAddr; break; }

	case	IDMxPluginPort_Cast_Text_GetLineCount: { subMxPluginPort_Cast_Text_GetLineCount = (TMxPluginPort_Cast_Text_GetLineCount)FuncAddr; break; }
	case	IDMxPluginPort_Cast_Text_GetLineString: { subMxPluginPort_Cast_Text_GetLineString = (TMxPluginPort_Cast_Text_GetLineString)FuncAddr; break; }

	case	IDMxPluginPort_Cast_TextML_GetLangAssigned: { subMxPluginPort_Cast_TextML_GetLangAssigned = (TMxPluginPort_Cast_TextML_GetLangAssigned)FuncAddr; break; }
	case	IDMxPluginPort_Cast_TextML_CreateLanguage: { subMxPluginPort_Cast_TextML_CreateLanguage = (TMxPluginPort_Cast_TextML_CreateLanguage)FuncAddr; break; }
	case	IDMxPluginPort_Cast_TextML_RemoveLanguage: { subMxPluginPort_Cast_TextML_RemoveLanguage = (TMxPluginPort_Cast_TextML_RemoveLanguage)FuncAddr; break; }

	case	IDMxPluginPort_End: {																										   break; }
	default: { return FALSE; };
	}
	return TRUE;
}

BOOL MxPluginPort_System_GetSDKEXEVersion(unsigned long long int* Version)
{
	if (Version) *Version = 0;
	if (subMxPluginPort_System_GetSDKVersion)
		return subMxPluginPort_System_GetSDKVersion(gsv_EXEVersion, Version);
	return false;
}

BOOL MxPluginPort_System_GetSDKFuncVersion(TSDKVersionList* Version)
{
	if (Version) *Version = svl_Unassigned;
	if (subMxPluginPort_System_GetSDKVersion)
		return subMxPluginPort_System_GetSDKVersion(gsv_FuncVersion, Version);
	return false;
}

BOOL MxPluginPort_System_AddMemu(HINSTANCE hinstDLL, char* Name, int Option, void* Reserved, void* UserParam)
{
	if (subMxPluginPort_System_AddMemu) return subMxPluginPort_System_AddMemu(hinstDLL, Name, Option, Reserved, UserParam);
	return false;
}

BOOL MxPluginPort_System_MenuEnabled(int hinstMenu, BOOL Enabled)
{
	if (subMxPluginPort_System_MenuEnabled) return subMxPluginPort_System_MenuEnabled(hinstMenu, Enabled);
	return false;
}

BOOL MxPluginPort_System_MenuVisible(int hinstMenu, BOOL Visible)
{
	if (subMxPluginPort_System_MenuVisible) return subMxPluginPort_System_MenuVisible(hinstMenu, Visible);
	return false;
}

BOOL MxPluginPort_System_MenuCaption(int hinstMenu, char* Caption)
{
	if (subMxPluginPort_System_MenuCaption) return subMxPluginPort_System_MenuCaption(hinstMenu, Caption);
	return false;
}

BOOL MxPluginPort_System_Paint(void* Reserved)
{
	if (subMxPluginPort_System_Paint) return subMxPluginPort_System_Paint(Reserved);
	return false;
}

BOOL MxPluginPort_System_AttachEvent(HINSTANCE hinstDLL, UINT msg, TMxWMCOPYDATAPROC lpWMCopyDataProc)
{
	if (subMxPluginPort_System_AttachEvent) return subMxPluginPort_System_AttachEvent(hinstDLL, msg, lpWMCopyDataProc);
	return false;
}

HWND MxPluginPort_System_GetHWnd(void)
{
	if (subMxPluginPort_System_GetHWnd) return subMxPluginPort_System_GetHWnd();
	return 0;
}

BOOL MxPluginPort_System_Progress(TSetProgressCommand Command, int Param)
{
	if (subMxPluginPort_System_Progress) return subMxPluginPort_System_Progress((int)Command, Param);
	return false;
}

BOOL MxPluginPort_System_ProgressMsg(char* Msg)
{
	if (subMxPluginPort_System_ProgressMsg) return subMxPluginPort_System_ProgressMsg((int)spg_SetMessage, Msg);
	return false;
}

BOOL MxPluginPort_System_TrimLabelName(char* Des, char* Sou)
{
	if (subMxPluginPort_System_TrimLabelName) return subMxPluginPort_System_TrimLabelName(Des, Sou);
	return false;
}

int MxPluginPort_System_GetSDKLanguage(void)
{
	if (subMxPluginPort_System_GetSDKLanguage) return subMxPluginPort_System_GetSDKLanguage();
	return 0;
}

BOOL MxPluginPort_System_ProcessMessages(void)
{
	if (subMxPluginPort_System_ProcessMessages) return subMxPluginPort_System_ProcessMessages();
	return false;
}

int MxPluginPort_Event_GetUIHandle(HINSTANCE hinstDLL, int* Handle)
{
	if (subMxPluginPort_Event_GetUIHandle) return subMxPluginPort_Event_GetUIHandle(hinstDLL, Handle);
	if (Handle != NULL) *Handle = 0;
	return 0;
}

BOOL MxPluginPort_Event_GetEventType(HINSTANCE hinstDLL, int* Type)
{
	if (subMxPluginPort_Event_GetEventType) return subMxPluginPort_Event_GetEventType(hinstDLL, Type);
	if (Type != NULL) *Type = -1;
	return false;
}

BOOL MxPluginPort_Event_GetPreEvent(HINSTANCE hinstDLL, BOOL* Flag)
{
	if (subMxPluginPort_Event_GetPreEvent) return subMxPluginPort_Event_GetPreEvent(hinstDLL, Flag);
	if (Flag != NULL) *Flag = false;
	return false;
}

BOOL MxPluginPort_Event_GetMXPFileName(HINSTANCE hinstDLL, char** FileName)
{
	if (subMxPluginPort_Event_GetMXPFileName) return subMxPluginPort_Event_GetMXPFileName(hinstDLL, FileName);
	if (FileName != NULL) *FileName = NULL;
	return false;
}

BOOL MxPluginPort_Event_Score_GetScoreTrack(HINSTANCE hinstDLL, int* ScoreNumber, int* TrackNumber)
{
	if (subMxPluginPort_Event_Score_GetScoreTrack) return subMxPluginPort_Event_Score_GetScoreTrack(hinstDLL, ScoreNumber, TrackNumber);
	if (ScoreNumber != NULL) *ScoreNumber = -1;
	if (TrackNumber != NULL) *TrackNumber = -1;
	return false;
}

BOOL MxPluginPort_Event_Score_GetSelectedCount(HINSTANCE hinstDLL, int* SelectedCount)
{
	if (subMxPluginPort_Event_Score_GetSelectedCount) return subMxPluginPort_Event_Score_GetSelectedCount(hinstDLL, SelectedCount);
	if (SelectedCount != NULL) *SelectedCount = 0;
	return false;
}

BOOL MxPluginPort_Event_Score_GetSelectedTrack(HINSTANCE hinstDLL, int Index, int* TrackNum)
{
	if (subMxPluginPort_Event_Score_GetSelectedTrack) return subMxPluginPort_Event_Score_GetSelectedTrack(hinstDLL, Index, TrackNum);
	if (TrackNum != NULL) *TrackNum = -1;
	return false;
}


BOOL MxPluginPort_Event_ScoreRename_GetNumber(HINSTANCE hinstDLL, int* ScoreNum)
{
	if (subMxPluginPort_Event_ScoreRename_GetNumber) return subMxPluginPort_Event_ScoreRename_GetNumber(hinstDLL, ScoreNum);
	if (ScoreNum != NULL) *ScoreNum = -1;
	return false;
}

BOOL MxPluginPort_Event_ScoreRename_GetOldName(HINSTANCE hinstDLL, char** OldName)
{
	if (subMxPluginPort_Event_ScoreRename_GetOldName) return subMxPluginPort_Event_ScoreRename_GetOldName(hinstDLL, OldName);
	if (OldName != NULL) *OldName = NULL;
	return false;
}

BOOL MxPluginPort_Event_ScoreRename_GetNewName(HINSTANCE hinstDLL, char** NewName)
{
	if (subMxPluginPort_Event_ScoreRename_GetNewName) return subMxPluginPort_Event_ScoreRename_GetNewName(hinstDLL, NewName);
	if (NewName != NULL) *NewName = NULL;
	return false;
}

BOOL MxPluginPort_Event_Cast_GetCastType(HINSTANCE hinstDLL, int* CastType)
{
	if (subMxPluginPort_Event_Cast_GetCastType) return subMxPluginPort_Event_Cast_GetCastType(hinstDLL, CastType);
	if (CastType != NULL) *CastType = -1;
	return false;
}

BOOL MxPluginPort_Event_Cast_GetCastNumber(HINSTANCE hinstDLL, int* CastNumber)
{
	if (subMxPluginPort_Event_Cast_GetCastNumber) return subMxPluginPort_Event_Cast_GetCastNumber(hinstDLL, CastNumber);
	if (CastNumber != NULL) *CastNumber = -1;
	return false;
}

BOOL MxPluginPort_Event_Cast_GetOldName(HINSTANCE hinstDLL, char** OldName)
{
	if (subMxPluginPort_Event_Cast_GetOldName) return subMxPluginPort_Event_Cast_GetOldName(hinstDLL, OldName);
	if (OldName != NULL) *OldName = NULL;
	return false;
}

BOOL MxPluginPort_Event_Cast_GetNewName(HINSTANCE hinstDLL, char** NewName)
{
	if (subMxPluginPort_Event_Cast_GetNewName) return subMxPluginPort_Event_Cast_GetNewName(hinstDLL, NewName);
	if (NewName != NULL) *NewName = NULL;
	return false;
}

BOOL MxPluginPort_Project_Init(int InitMode)
{
	if (subMxPluginPort_Project_Init) return subMxPluginPort_Project_Init(InitMode);
	return false;
}

BOOL MxPluginPort_Project_LoadCabinet(char* FileName, int Mode)
{
	if (subMxPluginPort_Project_LoadCabinet) return subMxPluginPort_Project_LoadCabinet(FileName, Mode);
	return false;
}

BOOL MxPluginPort_Project_LoadCabinetEx(char* FileName, int Mode, int* ScoreNumber, int* TrackNumber)
{
	if (subMxPluginPort_Project_LoadCabinetEx) return subMxPluginPort_Project_LoadCabinetEx(FileName, Mode, ScoreNumber, TrackNumber);
	return false;
}

BOOL MxPluginPort_Project_SetScreenSize(int width, int height)
{
	if (subMxPluginPort_Project_SetScreenSize) return subMxPluginPort_Project_SetScreenSize(width, height);
	return false;
}

char* MxPluginPort_Project_GetContentsPath(void)
{
	if (subMxPluginPort_Project_GetContentsPath) return subMxPluginPort_Project_GetContentsPath();
	return NULL;
}

char* MxPluginPort_Project_GetContentsName(void)
{
	if (subMxPluginPort_Project_GetContentsName) return subMxPluginPort_Project_GetContentsName();
	return NULL;
}

BOOL MxPluginPort_Project_GetContentsSaved(void)
{
	if (subMxPluginPort_Project_GetContentsSaved) return subMxPluginPort_Project_GetContentsSaved();
	return false;
}

BOOL MxPluginPort_Project_GetContentsChanged(void)
{
	if (subMxPluginPort_Project_GetContentsChanged) return subMxPluginPort_Project_GetContentsChanged();
	return false;
}

BOOL MxPluginPort_Project_SetContentsChanged(void)
{
	if (subMxPluginPort_Project_SetContentsChanged) return subMxPluginPort_Project_SetContentsChanged();
	return false;
}

BOOL MxPluginPort_Project_ClearContentsChanged(void)
{
	if (subMxPluginPort_Project_ClearContentsChanged) return subMxPluginPort_Project_ClearContentsChanged();
	return false;
}

BOOL MxPluginPort_Project_SaveContents(char* FileName)
{
	if (subMxPluginPort_Project_SaveContents) return subMxPluginPort_Project_SaveContents(FileName);
	return false;
}

BOOL MxPluginPort_Project_LoadContents(char* FileName)
{
	if (subMxPluginPort_Project_LoadContents) return subMxPluginPort_Project_LoadContents(FileName);
	return false;
}

BOOL MxPluginPort_Project_CreateRuntimeFile(char* FileName, int Format, void* Options)
{
	if (subMxPluginPort_Project_CreateRuntimeFile) return subMxPluginPort_Project_CreateRuntimeFile(FileName, Format, Options);
	return false;
}

BOOL MxPluginPort_Project_GetContentsRunning(void)
{
	if (subMxPluginPort_Project_GetContentsRunning) return subMxPluginPort_Project_GetContentsRunning();
	return false;
}

BOOL MxPluginPort_Project_LoadFile(char* FileName, int Format, void* Options)
{
	if (subMxPluginPort_Project_LoadFile) return subMxPluginPort_Project_LoadFile(FileName, Format, Options);
	return false;
}

BOOL MxPluginPort_CLang_GetEnabled(void)
{
	if (subMxPluginPort_CLang_GetEnabled) return subMxPluginPort_CLang_GetEnabled();
	return false;
}

BOOL MxPluginPort_CLang_GetPathSRC(char** FileName)
{
	if (FileName) *FileName = NULL;
	if (subMxPluginPort_CLang_GetPathSRC) return subMxPluginPort_CLang_GetPathSRC(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetPathEvent(char** FileName)
{
	if (FileName) *FileName = NULL;
	if (subMxPluginPort_CLang_GetPathEvent) return subMxPluginPort_CLang_GetPathEvent(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetPathLib(char** FileName)
{
	if (FileName) *FileName = NULL;
	if (subMxPluginPort_CLang_GetPathLib) return subMxPluginPort_CLang_GetPathLib(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetPathOBJ(char** FileName)
{
	if (FileName) *FileName = NULL;
	if (subMxPluginPort_CLang_GetPathOBJ) return subMxPluginPort_CLang_GetPathOBJ(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetFileNameConst(char** FileName)
{
	if (FileName) *FileName = NULL;
	if (subMxPluginPort_CLang_GetFileNameConst) return subMxPluginPort_CLang_GetFileNameConst(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetFileNameEventSource(char** FileName)
{
	if (FileName) *FileName = NULL;
	if (subMxPluginPort_CLang_GetFileNameEventSource) return subMxPluginPort_CLang_GetFileNameEventSource(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetFileNameEventHeader(char** FileName)
{
	if (FileName) *FileName = NULL;
	if (subMxPluginPort_CLang_GetFileNameEventHeader) return subMxPluginPort_CLang_GetFileNameEventHeader(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetInitEvent_Enabled(BOOL* Enabled)
{
	if (Enabled) *Enabled = false;
	if (subMxPluginPort_CLang_GetInitEvent_Enabled) return subMxPluginPort_CLang_GetInitEvent_Enabled(Enabled);
	return false;
}

BOOL MxPluginPort_CLang_GetInitEvent_Type(TCLang_EventNameType* Type)
{
	if (Type) *Type = evt_DefaultName;
	if (subMxPluginPort_CLang_GetInitEvent_Type) {
		int iType;
		BOOL res = subMxPluginPort_CLang_GetInitEvent_Type(&iType);
		if (res) {
			*Type = (TCLang_EventNameType)iType;
		}
		return res;
	}
	return false;
}

BOOL MxPluginPort_CLang_GetInitEvent_Name(char** Name)
{
	if (Name) *Name = NULL;
	if (subMxPluginPort_CLang_GetInitEvent_Name) return subMxPluginPort_CLang_GetInitEvent_Name(Name);
	return false;
}

BOOL MxPluginPort_CLang_GetFinallyEvent_Enabled(BOOL* Enabled)
{
	if (Enabled) *Enabled = false;
	if (subMxPluginPort_CLang_GetFinallyEvent_Enabled) return subMxPluginPort_CLang_GetFinallyEvent_Enabled(Enabled);
	return false;
}

BOOL MxPluginPort_CLang_GetFinallyEvent_Type(TCLang_EventNameType* Type)
{
	if (Type) *Type = evt_DefaultName;
	if (subMxPluginPort_CLang_GetFinallyEvent_Type) {
		int iType;
		BOOL res = subMxPluginPort_CLang_GetFinallyEvent_Type(&iType);
		if (res) {
			*Type = (TCLang_EventNameType)iType;
		}
		return res;
	}
	return false;
}

BOOL MxPluginPort_CLang_GetFinallyEvent_Name(char** Name)
{
	if (Name) *Name = NULL;
	if (subMxPluginPort_CLang_GetFinallyEvent_Name) return subMxPluginPort_CLang_GetFinallyEvent_Name(Name);
	return false;
}

BOOL MxPluginPort_CLang_GetInitEventFuncName(char** Name)
{
	if (Name) *Name = NULL;
	if (subMxPluginPort_CLang_GetInitEventFuncName) return subMxPluginPort_CLang_GetInitEventFuncName(Name);
	return false;
}

BOOL MxPluginPort_CLang_GetFinallyEventFuncName(char** Name)
{
	if (Name) *Name = NULL;
	if (subMxPluginPort_CLang_GetFinallyEventFuncName) return subMxPluginPort_CLang_GetFinallyEventFuncName(Name);
	return false;
}

BOOL MxPluginPort_CLang_SetEnabled(BOOL Enabled)
{
	if (subMxPluginPort_CLang_SetEnabled) return subMxPluginPort_CLang_SetEnabled(Enabled);
	return false;
}

BOOL MxPluginPort_CLang_SetPathSRCNative(char* FileName)
{
	if (subMxPluginPort_CLang_SetPathSRCNative) return subMxPluginPort_CLang_SetPathSRCNative(FileName);
	return false;
}

BOOL MxPluginPort_CLang_SetPathEventNative(char* FileName)
{
	if (subMxPluginPort_CLang_SetPathEventNative) return subMxPluginPort_CLang_SetPathEventNative(FileName);
	return false;
}

BOOL MxPluginPort_CLang_SetPathLibNative(char* FileName)
{
	if (subMxPluginPort_CLang_SetPathLibNative) return subMxPluginPort_CLang_SetPathLibNative(FileName);
	return false;
}

BOOL MxPluginPort_CLang_SetPathOBJNative(char* FileName)
{
	if (subMxPluginPort_CLang_SetPathOBJNative) return subMxPluginPort_CLang_SetPathOBJNative(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetPathSRCNative(char** FileName)
{
	if (subMxPluginPort_CLang_GetPathSRCNative) return subMxPluginPort_CLang_GetPathSRCNative(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetPathEventNative(char** FileName)
{
	if (subMxPluginPort_CLang_GetPathEventNative) return subMxPluginPort_CLang_GetPathEventNative(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetPathLibNative(char** FileName)
{
	if (subMxPluginPort_CLang_GetPathLibNative) return subMxPluginPort_CLang_GetPathLibNative(FileName);
	return false;
}

BOOL MxPluginPort_CLang_GetPathOBJNative(char** FileName)
{
	if (subMxPluginPort_CLang_GetPathOBJNative) return subMxPluginPort_CLang_GetPathOBJNative(FileName);
	return false;
}


BOOL MxPluginPort_CLang_SetInitEvent_Enabled(BOOL Enabled)
{
	if (subMxPluginPort_CLang_SetInitEvent_Enabled) return subMxPluginPort_CLang_SetInitEvent_Enabled(Enabled);
	return false;
}

BOOL MxPluginPort_CLang_SetInitEvent_Type(TCLang_EventNameType Value)
{
	if (subMxPluginPort_CLang_SetInitEvent_Type) return subMxPluginPort_CLang_SetInitEvent_Type((int)Value);
	return false;
}

BOOL MxPluginPort_CLang_SetInitEvent_Name(char* Name)
{
	if (subMxPluginPort_CLang_SetInitEvent_Name) return subMxPluginPort_CLang_SetInitEvent_Name(Name);
	return false;
}

BOOL MxPluginPort_CLang_SetFinallyEvent_Enabled(BOOL Enabled)
{
	if (subMxPluginPort_CLang_SetFinallyEvent_Enabled) return subMxPluginPort_CLang_SetFinallyEvent_Enabled(Enabled);
	return false;
}

BOOL MxPluginPort_CLang_SetFinallyEvent_Type(TCLang_EventNameType Value)
{
	if (subMxPluginPort_CLang_SetFinallyEvent_Type) return subMxPluginPort_CLang_SetFinallyEvent_Type((int)Value);
	return false;
}

BOOL MxPluginPort_CLang_SetFinallyEvent_Name(char* Name)
{
	if (subMxPluginPort_CLang_SetFinallyEvent_Name) return subMxPluginPort_CLang_SetFinallyEvent_Name(Name);
	return false;
}

BOOL MxPluginPort_CLang_SetEventListName_Type(TCLang_EventNameType Value)
{
	if (subMxPluginPort_CLang_SetEventListName_Type) return subMxPluginPort_CLang_SetEventListName_Type((int)Value);
	return false;
}

BOOL MxPluginPort_CLang_SetEventListName_Name(char* Name)
{
	if (subMxPluginPort_CLang_SetEventListName_Name) return subMxPluginPort_CLang_SetEventListName_Name(Name);
	return false;
}

BOOL MxPluginPort_CLang_SetEventSymbolName_Type(TCLang_EventNameType Value)
{
	if (subMxPluginPort_CLang_SetEventSymbolName_Type) return subMxPluginPort_CLang_SetEventSymbolName_Type((int)Value);
	return false;
}

BOOL MxPluginPort_CLang_SetEventSymbolName_Name(char* Name)
{
	if (subMxPluginPort_CLang_SetEventSymbolName_Name) return subMxPluginPort_CLang_SetEventSymbolName_Name(Name);
	return false;
}

BOOL MxPluginPort_CLang_SetEventTableName_Type(TCLang_EventNameType Value)
{
	if (subMxPluginPort_CLang_SetEventTableName_Type) return subMxPluginPort_CLang_SetEventTableName_Type((int)Value);
	return false;
}

BOOL MxPluginPort_CLang_SetEventTableName_Name(char* Name)
{
	if (subMxPluginPort_CLang_SetEventTableName_Name) return subMxPluginPort_CLang_SetEventTableName_Name(Name);
	return false;
}

BOOL MxPluginPort_CLang_SetEventTableName_Alias(BOOL Enabled)
{
	if (subMxPluginPort_CLang_SetEventTableName_Alias) return subMxPluginPort_CLang_SetEventTableName_Alias(Enabled);
	return false;
}

BOOL MxPluginPort_Project_MultiLang_GetEnabled(BOOL* Enabled)
{
	if (Enabled) *Enabled = false;
	if (subMxPluginPort_Project_MultiLang_GetEnabled) return subMxPluginPort_Project_MultiLang_GetEnabled(Enabled);
	return false;
}

BOOL MxPluginPort_Project_MultiLang_SetEnabled(BOOL	Enabled)
{
	if (subMxPluginPort_Project_MultiLang_SetEnabled) return subMxPluginPort_Project_MultiLang_SetEnabled(Enabled);
	return false;
}

BOOL MxPluginPort_Project_MultiLang_GetCount(int* Count)
{
	if (subMxPluginPort_Project_MultiLang_GetCount) return subMxPluginPort_Project_MultiLang_GetCount(Count);
	return false;
}

BOOL MxPluginPort_Project_MultiLang_GetName(int	Index, char** Name)
{
	if (Name) *Name = NULL;
	if (subMxPluginPort_Project_MultiLang_GetName) return subMxPluginPort_Project_MultiLang_GetName(Index, Name);
	return false;
}

BOOL MxPluginPort_Project_MultiLang_SetName(int Index, const char* Name)
{
	if (subMxPluginPort_Project_MultiLang_SetName) return subMxPluginPort_Project_MultiLang_SetName(Index, Name);
	return false;
}

BOOL MxPluginPort_Project_MultiLang_Add(const char* Name)
{
	if (subMxPluginPort_Project_MultiLang_Add) return subMxPluginPort_Project_MultiLang_Add(Name);
	return false;
}

BOOL MxPluginPort_Project_MultiLang_Remove(int Index)
{
	if (subMxPluginPort_Project_MultiLang_Remove) return subMxPluginPort_Project_MultiLang_Remove(Index);
	return false;
}

int  MxPluginPort_Cast_FindBlank(int CastType)
{
	if (subMxPluginPort_Cast_FindBlank) return subMxPluginPort_Cast_FindBlank(CastType);
	return -1;
}

int  MxPluginPort_Cast_FindBlankSince(int CastType, int CastNumber)
{
	if (subMxPluginPort_Cast_FindBlankSince) return subMxPluginPort_Cast_FindBlankSince(CastType, CastNumber);
	return -1;
}

int  MxPluginPort_Cast_GetCastCount(int CastType)
{
	if (subMxPluginPort_Cast_GetCastCount) return subMxPluginPort_Cast_GetCastCount(CastType);
	return -1;
}

int  MxPluginPort_Cast_CreateCamera(int CastNumber, char* CastName)
{
	if (subMxPluginPort_Cast_CreateCamera) return subMxPluginPort_Cast_CreateCamera(CastNumber, CastName);
	return -1;
}

int  MxPluginPort_Cast_CreateLight(int CastNumber, char* CastName, int LightType)
{
	if (subMxPluginPort_Cast_CreateLight) return subMxPluginPort_Cast_CreateLight(CastNumber, CastName, LightType);
	return -1;
}

BOOL MxPluginPort_Cast_Delete(int CastType, int CastNumber, int Reserved)
{
	if (subMxPluginPort_Cast_Delete) return subMxPluginPort_Cast_Delete(CastType, CastNumber, Reserved);
	return false;
}

BOOL MxPluginPort_Cast_UseCheck(int CastType, int CastNumber)
{
	if (subMxPluginPort_Cast_UseCheck) return subMxPluginPort_Cast_UseCheck(CastType, CastNumber);
	return false;
}

int  MxPluginPort_Cast_GetCastName(int CastType, int CastNumber, char* CastName, int NameLength)
{
	if (subMxPluginPort_Cast_GetCastName) return subMxPluginPort_Cast_GetCastName(CastType, CastNumber, CastName, NameLength);
	return 0;
}

int  MxPluginPort_Cast_SetCastName(int CastType, int CastNumber, char* NewName, BOOL OverWrite)
{
	if (subMxPluginPort_Cast_SetCastName) return subMxPluginPort_Cast_SetCastName(CastType, CastNumber, NewName, OverWrite);
	return 0;
}

BOOL MxPluginPort_Cast_SaveToFile(int CastType, int CastNumbe, char* FileName, void* Reserved)
{
	if (subMxPluginPort_Cast_SaveToFile) return subMxPluginPort_Cast_SaveToFile(CastType, CastNumbe, FileName, Reserved);
	return false;
}

int  MxPluginPort_Cast_FindCast(int CastType, char* CastName)
{
	if (subMxPluginPort_Cast_FindCast) return subMxPluginPort_Cast_FindCast(CastType, CastName);
	return -1;
}

int  MxPluginPort_Cast_CreateWave(int CastNumber, char* CastName, char* FileName, BOOL ExternalFile)
{
	if (subMxPluginPort_Cast_CreateWave) return subMxPluginPort_Cast_CreateWave(CastNumber, CastName, FileName, ExternalFile);
	return -1;
}

int  MxPluginPort_Cast_CreateText(int CastNumber, char* CastName)
{
	if (subMxPluginPort_Cast_CreateText) return subMxPluginPort_Cast_CreateText(CastNumber, CastName);
	return -1;
}

int  MxPluginPort_Cast_CreateScript(int CastNumber, char* CastName)
{
	if (subMxPluginPort_Cast_CreateScript) return subMxPluginPort_Cast_CreateScript(CastNumber, CastName);
	return -1;
}

int  MxPluginPort_Cast_CreateScriptEx(int CastNumber, char* CastName, char* FileName, int Options, int Reserved)
{
	if (subMxPluginPort_Cast_CreateScriptEx) return subMxPluginPort_Cast_CreateScriptEx(CastNumber, CastName, FileName, Options, Reserved);
	return -1;
}

int  MxPluginPort_Cast_CreateTexture(int CastNumber, char* CastName, char* FileName)
{
	if (subMxPluginPort_Cast_CreateTexture) return subMxPluginPort_Cast_CreateTexture(CastNumber, CastName, FileName);
	return -1;
}

int  MxPluginPort_Cast_CreateTextureEx(int CastNumber, char* CastName, char* FileName, int Option, int Reserved)
{
	if (subMxPluginPort_Cast_CreateTextureEx) return subMxPluginPort_Cast_CreateTextureEx(CastNumber, CastName, FileName, Option, Reserved);
	return -1;
}

int  MxPluginPort_Cast_CreateBitmap(int CastNumber, char* CastName, char* FileName)
{
	if (subMxPluginPort_Cast_CreateBitmap) return subMxPluginPort_Cast_CreateBitmap(CastNumber, CastName, FileName);
	return -1;
}

BOOL MxPluginPort_Cast_Assigned(int CastType, int CastNumber)
{
	if (subMxPluginPort_Cast_Assigned) return subMxPluginPort_Cast_Assigned(CastType, CastNumber);
	return false;
}

int  MxPluginPort_Cast_TrimCastName(int CastType, char* SourCastName, char* DestCastName, int NameLength)
{
	if (subMxPluginPort_Cast_TrimCastName) return subMxPluginPort_Cast_TrimCastName(CastType, SourCastName, DestCastName, NameLength);
	return 0;
}

BOOL MxPluginPort_Cast_TrimFileName(int CastType, int CastNumber)
{
	if (subMxPluginPort_Cast_TrimFileName) return subMxPluginPort_Cast_TrimFileName(CastType, CastNumber);
	return false;
}

BOOL MxPluginPort_Cast_Exchange(int CastType, int CastNumber1, int CastNumber2)
{
	if (subMxPluginPort_Cast_Exchange) return subMxPluginPort_Cast_Exchange(CastType, CastNumber1, CastNumber2);
	return false;
}

BOOL MxTest_PluginPort_Cast_TrimCastName(void)
{
	return (subMxPluginPort_Cast_TrimCastName) ? true : false;
}


int  MxPluginPort_Score_GetScoreName(int ScoreNumber, char* ScoreName, int NameLength)
{
	if (subMxPluginPort_Score_GetScoreName) return subMxPluginPort_Score_GetScoreName(ScoreNumber, ScoreName, NameLength);
	return 0;
}

int  MxPluginPort_Score_GetScoreCount(void)
{
	if (subMxPluginPort_Score_GetScoreCount) return subMxPluginPort_Score_GetScoreCount();
	return -1;
}

int  MxPluginPort_Score_GetTrackCount(int ScoreNumber)
{
	if (subMxPluginPort_Score_GetTrackCount) return subMxPluginPort_Score_GetTrackCount(ScoreNumber);
	return -1;
}

int  MxPluginPort_Score_CreateScore(char* ScoreName, int* TrackNumber)
{
	if (subMxPluginPort_Score_CreateScore) return subMxPluginPort_Score_CreateScore(ScoreName, TrackNumber);
	return -1;
}

int  MxPluginPort_Score_CreateTrack(int ScoreNumber, int CastType, int CastNumber)
{
	if (subMxPluginPort_Score_CreateTrack) return subMxPluginPort_Score_CreateTrack(ScoreNumber, CastType, CastNumber);
	return -1;
}

BOOL MxPluginPort_Score_DeleteTrack(int ScoreNumber, int TrackNumber, int Reserved)
{
	if (subMxPluginPort_Score_DeleteTrack) return subMxPluginPort_Score_DeleteTrack(ScoreNumber, TrackNumber, Reserved);
	return false;
}

BOOL MxPluginPort_Score_Trim(int ScoreNumber)
{
	if (subMxPluginPort_Score_Trim) return subMxPluginPort_Score_Trim(ScoreNumber);
	return false;
}

int  MxPluginPort_Score_GetLength(int ScoreNumber)
{
	if (subMxPluginPort_Score_GetLength) return subMxPluginPort_Score_GetLength(ScoreNumber);
	return -1;
}

int  MxPluginPort_Score_Find(char* ScoreName)
{
	if (subMxPluginPort_Score_Find) return subMxPluginPort_Score_Find(ScoreName);
	return -1;
}

BOOL MxPluginPort_Score_UpdateLength(int ScoreNumber)
{
	if (subMxPluginPort_Score_UpdateLength) return subMxPluginPort_Score_UpdateLength(ScoreNumber);
	return false;
}

BOOL MxPluginPort_Score_Exchange(int ScoreNumber, int Track1, int Track2)
{
	if (subMxPluginPort_Score_Exchange) return subMxPluginPort_Score_Exchange(ScoreNumber, Track1, Track2);
	return false;
}

BOOL MxPluginPort_Score_DeleteScore(int ScoreNumber)
{
	if (subMxPluginPort_Score_DeleteScore) return subMxPluginPort_Score_DeleteScore(ScoreNumber);
	return false;
}

int  MxPluginPort_Score_GetLabelName(int ScoreNumber, int FrameNumber, char* LabelName, int NameLength)
{
	if (subMxPluginPort_Score_GetLabelName) return subMxPluginPort_Score_GetLabelName(ScoreNumber, FrameNumber, LabelName, NameLength);
	return 0;
}

BOOL MxPluginPort_Score_SetLabelName(int ScoreNumber, int FrameNumber, char* LabelName, int Reserved)
{
	if (subMxPluginPort_Score_SetLabelName) return subMxPluginPort_Score_SetLabelName(ScoreNumber, FrameNumber, LabelName, Reserved);
	return false;
}

int  MxPluginPort_Score_GetLabelPosMax(int ScoreNumber)
{
	if (subMxPluginPort_Score_GetLabelPosMax) return subMxPluginPort_Score_GetLabelPosMax(ScoreNumber);
	return -1;
}

int  MxPluginPort_Score_FindFrameLabel(int ScoreNumber, char* LabelName)
{
	if (subMxPluginPort_Score_FindFrameLabel) return subMxPluginPort_Score_FindFrameLabel(ScoreNumber, LabelName);
	return -1;
}

BOOL MxPluginPort_Score_Clear(int ScoreNumber, int Options)
{
	if (subMxPluginPort_Score_Clear) return subMxPluginPort_Score_Clear(ScoreNumber, Options);
	return false;
}

BOOL MxPluginPort_Score_MoveTrack(int ScoreNumber, int MoveTo, int MoveFrom)
{
	if (subMxPluginPort_Score_MoveTrack) return subMxPluginPort_Score_MoveTrack(ScoreNumber, MoveTo, MoveFrom);
	return false;
}

BOOL MxTest_MxPluginPort_Score_Clear(void)
{
	return (subMxPluginPort_Score_Clear) ? true : false;
}

BOOL MxPluginPort_Score_SetAnnotationEncode(int ScoreNumber, TAnnotationEncode Encode)
{
	if (subMxPluginPort_Score_SetAnnotationEncode) return subMxPluginPort_Score_SetAnnotationEncode(ScoreNumber, (int)Encode);
	return false;
}

BOOL MxPluginPort_Score_SetAnnotationData(int ScoreNumber, int Page, void* Annotation)
{
	if (subMxPluginPort_Score_SetAnnotationData) return subMxPluginPort_Score_SetAnnotationData(ScoreNumber, Page, Annotation);
	return false;
}

BOOL MxPluginPort_Score_GetAnnotationEncode(int ScoreNumber, TAnnotationEncode* Encode)
{
	if (Encode) *Encode = sae_UNSET;
	if (subMxPluginPort_Score_GetAnnotationEncode) {
		int encode_int;
		BOOL res = subMxPluginPort_Score_GetAnnotationEncode(ScoreNumber, &encode_int);
		if (Encode) *Encode = (TAnnotationEncode)encode_int;
		return res;
	}
	return false;
}

BOOL MxPluginPort_Score_GetAnnotationData(int ScoreNumber, int Page, void** Annotation)
{
	if (Annotation)
		*Annotation = NULL;
	if (subMxPluginPort_Score_GetAnnotationData) return subMxPluginPort_Score_GetAnnotationData(ScoreNumber, Page, Annotation);
	return false;
}

BOOL MxPluginPort_Score_GetAnnotationCount(int ScoreNumber, int* Count)
{
	if (subMxPluginPort_Score_GetAnnotationCount) return subMxPluginPort_Score_GetAnnotationCount(ScoreNumber, Count);
	return false;
}

BOOL MxPluginPort_Score_ClearAnnotation(int ScoreNumber, int Page)
{
	if (subMxPluginPort_Score_ClearAnnotation) return subMxPluginPort_Score_ClearAnnotation(ScoreNumber, Page);
	return false;
}

int MxPluginPort_Score_InsertAnnotationData(int ScoreNumber, int Page, void* Annotation)
{
	if (subMxPluginPort_Score_InsertAnnotationData) return subMxPluginPort_Score_InsertAnnotationData(ScoreNumber, Page, Annotation);
	return -1;
}

BOOL MxPluginPort_Score_RemoveAnnotationData(int ScoreNumber, int Page)
{
	if (subMxPluginPort_Score_RemoveAnnotationData) return subMxPluginPort_Score_RemoveAnnotationData(ScoreNumber, Page);
	return false;
}

BOOL MxPluginPort_Track_GetCastType(int ScoreNumber, int TrackNumber, int* CastType)
{
	if (subMxPluginPort_Track_GetCastType) return subMxPluginPort_Track_GetCastType(ScoreNumber, TrackNumber, CastType);
	return false;
}

BOOL MxPluginPort_Track_GetCastNumber(int ScoreNumber, int TrackNumber, int* CastNumber)
{
	if (subMxPluginPort_Track_GetCastNumber) return subMxPluginPort_Track_GetCastNumber(ScoreNumber, TrackNumber, CastNumber);
	return false;
}

BOOL MxPluginPort_Track_SetCastNumber(int ScoreNumber, int TrackNumber, int CastNumber)
{
	if (subMxPluginPort_Track_SetCastNumber) return subMxPluginPort_Track_SetCastNumber(ScoreNumber, TrackNumber, CastNumber);
	return false;
}

int  MxPluginPort_Track_GetLength(int ScoreNumber, int TrackNumber)
{
	if (subMxPluginPort_Track_GetLength) return subMxPluginPort_Track_GetLength(ScoreNumber, TrackNumber);
	return -1;
}

BOOL MxPluginPort_Track_GetParent(int ScoreNumber, int TrackNumber, int* ParentTrackNumber)
{
	if (subMxPluginPort_Track_GetParent) return subMxPluginPort_Track_GetParent(ScoreNumber, TrackNumber, ParentTrackNumber);
	return false;
}

BOOL MxPluginPort_Track_TestSetParent(int ScoreNumber, int ParentTrack, int ChildTrack)
{
	if (subMxPluginPort_Track_TestSetParent) return subMxPluginPort_Track_TestSetParent(ScoreNumber, ParentTrack, ChildTrack);
	return false;
}

BOOL MxPluginPort_Track_SetParent(int ScoreNumber, int ParentTrack, int ChildTrack)
{
	if (subMxPluginPort_Track_SetParent) return subMxPluginPort_Track_SetParent(ScoreNumber, ParentTrack, ChildTrack);
	return false;
}

BOOL MxPluginPort_Track_GetFrameData(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType, void* Data)
{
	if (subMxPluginPort_Track_GetFrameData) return subMxPluginPort_Track_GetFrameData(ScoreNumber, TrackNumber, FrameNumber, TrackType, Data);
	return false;
}

BOOL MxPluginPort_Track_SetFrameData(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType, void* Data)
{
	if (subMxPluginPort_Track_SetFrameData) return subMxPluginPort_Track_SetFrameData(ScoreNumber, TrackNumber, FrameNumber, TrackType, Data);
	return false;
}

BOOL MxPluginPort_Track_Trim(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType)
{
	if (subMxPluginPort_Track_Trim) return subMxPluginPort_Track_Trim(ScoreNumber, TrackNumber, FrameNumber, TrackType);
	return false;
}

BOOL MxPluginPort_Track_Assigned(int ScoreNumber, int TrackNumber)
{
	if (subMxPluginPort_Track_Assigned) return subMxPluginPort_Track_Assigned(ScoreNumber, TrackNumber);
	return false;
}

int  MxPluginPort_Track_FindBlank(int ScoreNumber)
{
	if (subMxPluginPort_Track_FindBlank) return subMxPluginPort_Track_FindBlank(ScoreNumber);
	return -1;
}

BOOL MxPluginPort_Track_SetAttribute(int ScoreNumber, int TrackNumber, int AttrType, BOOL Value)
{
	if (subMxPluginPort_Track_SetAttribute) return subMxPluginPort_Track_SetAttribute(ScoreNumber, TrackNumber, AttrType, Value);
	return false;
}

BOOL MxPluginPort_Track_GetAttribute(int ScoreNumber, int TrackNumber, int AttrType, BOOL* Value)
{
	if (subMxPluginPort_Track_GetAttribute) return subMxPluginPort_Track_GetAttribute(ScoreNumber, TrackNumber, AttrType, Value);
	return false;
}

int  MxPluginPort_Track_GetLabelName(int ScoreNumber, int TrackNumber, char* LabelName, int NameLength)
{
	if (subMxPluginPort_Track_GetLabelName) return subMxPluginPort_Track_GetLabelName(ScoreNumber, TrackNumber, LabelName, NameLength);
	return 0;
}

BOOL MxPluginPort_Track_SetLabelName(int ScoreNumber, int TrackNumber, char* LabelName, int Reserved)
{
	if (subMxPluginPort_Track_SetLabelName) return subMxPluginPort_Track_SetLabelName(ScoreNumber, TrackNumber, LabelName, Reserved);
	return false;
}

int  MxPluginPort_Track_FindTrackLabel(int ScoreNumber, char* LabelName)
{
	if (subMxPluginPort_Track_FindTrackLabel) return subMxPluginPort_Track_FindTrackLabel(ScoreNumber, LabelName);
	return -1;
}

BOOL MxPluginPort_TrackProperty_SetData(int ScoreNumber, int TrackNumber, int IDNum, int Value)
{
	if (subMxPluginPort_TrackProperty_SetData) return subMxPluginPort_TrackProperty_SetData(ScoreNumber, TrackNumber, IDNum, Value);
	return false;
}

BOOL MxPluginPort_TrackProperty_GetData(int ScoreNumber, int TrackNumber, int IDNum, void* Value)
{
	if (subMxPluginPort_TrackProperty_GetData) return subMxPluginPort_TrackProperty_GetData(ScoreNumber, TrackNumber, IDNum, Value);
	return false;
}

int  MxPluginPort_LoopTrack_GetLength(int ScoreNumbe)
{
	if (subMxPluginPort_LoopTrack_GetLength) return subMxPluginPort_LoopTrack_GetLength(ScoreNumbe);
	return -1;
}

BOOL MxPluginPort_LoopTrack_GetValue(int ScoreNumber, int FrameNumber, TLoopTrackData* Value)
{
	int iVal = 0;
	if (subMxPluginPort_LoopTrack_GetValue) return subMxPluginPort_LoopTrack_GetValue(ScoreNumber, FrameNumber, &iVal);
	*Value = (TLoopTrackData)(iVal & 0xff);
	return false;
}

BOOL MxPluginPort_LoopTrack_SetValue(int ScoreNumber, int FrameNumber, TLoopTrackData Value)
{
	if (subMxPluginPort_LoopTrack_SetValue) return subMxPluginPort_LoopTrack_SetValue(ScoreNumber, FrameNumber, (int)Value);
	return false;
}

BOOL MxPluginPort_LoopTrack_Trim(int ScoreNumber)
{
	if (subMxPluginPort_LoopTrack_Trim) return subMxPluginPort_LoopTrack_Trim(ScoreNumber);
	return false;
}

BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value)
{
	if (subMxPluginPort_CastPropety_SetDataInt1) return subMxPluginPort_CastPropety_SetDataInt1(CastType, CastNumber, PropertyType, Value);
	return false;
}

BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value1, int Value2)
{
	if (subMxPluginPort_CastPropety_SetDataInt2) return subMxPluginPort_CastPropety_SetDataInt2(CastType, CastNumber, PropertyType, Value1, Value2);
	return false;
}

BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value1, int Value2, int Value3)
{
	if (subMxPluginPort_CastPropety_SetDataInt3) return subMxPluginPort_CastPropety_SetDataInt3(CastType, CastNumber, PropertyType, Value1, Value2, Value3);
	return false;
}

BOOL MxPluginPort_CastPropety_SetDataPtr(int CastType, int CastNumber, int PropertyType, void* Value)
{
	if (subMxPluginPort_CastPropety_SetDataPtr) return subMxPluginPort_CastPropety_SetDataPtr(CastType, CastNumber, PropertyType, Value);
	return false;
}

BOOL MxPluginPort_CastPropety_SetDataFloat(int CastType, int CastNumber, int PropertyType, float Value)
{
	if (subMxPluginPort_CastPropety_SetDataFloat) return subMxPluginPort_CastPropety_SetDataFloat(CastType, CastNumber, PropertyType, Value);
	return false;
}

BOOL MxPluginPort_CastPropety_GetData(int CastType, int CastNumber, int PropertyType, void* Value)
{
	if (subMxPluginPort_CastPropety_GetData) return subMxPluginPort_CastPropety_GetData(CastType, CastNumber, PropertyType, Value);
	return false;
}

BOOL MxPluginPort_Primitive_QuadPolygon(int CastNumber, char* CastName, MXPLUGIN_VECTOR3D V1, MXPLUGIN_VECTOR3D V2, MXPLUGIN_VECTOR3D V3, MXPLUGIN_VECTOR3D V4)
{
	if (subMxPluginPort_Primitive_QuadPolygon) return subMxPluginPort_Primitive_QuadPolygon(CastNumber, CastName, V1, V2, V3, V4);
	return false;
}

BOOL MxCast_Bitmap_SetDataInt(int CastNumber, TBitmapPropertyType PropertyType, int Value) { return MxPluginPort_CastPropety_SetDataInt(ct_Bitmap, CastNumber, (int)PropertyType, Value); }
BOOL MxCast_Bitmap_GetDataInt(int CastNumber, TBitmapPropertyType PropertyType, int* Value) { return MxPluginPort_CastPropety_GetData(ct_Bitmap, CastNumber, (int)PropertyType, Value); }
BOOL MxCast_Text_SetDataInt(int CastNumber, TTextPropertyType PropertyType, int Value) { return MxPluginPort_CastPropety_SetDataInt(ct_Text, CastNumber, (int)PropertyType, Value); }
BOOL MxCast_Text_GetDataInt(int CastNumber, TTextPropertyType PropertyType, int* Value) { return MxPluginPort_CastPropety_GetData(ct_Text, CastNumber, (int)PropertyType, Value); }

BOOL MxPluginPort_Script_GetEncode(int CastNumber, TScriptEncodeType* Value)
{
	int intval;
	BOOL res = MxPluginPort_CastPropety_GetData(ct_Script, CastNumber, cp_Script_Encode, &intval);
	if (res) {
		switch (intval) {
		case 0:			*Value = script_encode_ANSI;		break;
		case 1:			*Value = script_encode_UTF8;		break;
		case 2:			*Value = script_encode_UTF8_BOM;	break;
		default:		res = false;						break;
		}
	}
	return res;
}

BOOL MxPluginPort_Script_GetExternal(int CastNumber, TScriptExternalFile* Value)
{
	int intval;
	BOOL res = MxPluginPort_CastPropety_GetData(ct_Script, CastNumber, cp_Script_External, &intval);
	if (res) {
		switch (intval) {
		case 0:			*Value = script_file_Internal;	break;
		case 1:			*Value = script_file_External;	break;
		default:		res = false;				break;
		}
	}
	return res;
}

BOOL MxPluginPort_Project_SetPropertyInt(TProjectProperty ID, int Value)
{
	if (subMxPluginPort_Project_SetPropertyInt) return subMxPluginPort_Project_SetPropertyInt(ID, Value);
	return false;
}


BOOL MxPluginPort_Project_GetPropertyInt(TProjectProperty ID, int* Value)
{
	if (subMxPluginPort_Project_GetPropertyInt) return subMxPluginPort_Project_GetPropertyInt(ID, Value);
	return false;
}

BOOL MxPluginPort_Cast_Text_GetLineCount(int CastNumber, int LangNum, int* Count)
{
	if (Count != NULL) *Count = 0;
	if (subMxPluginPort_Cast_Text_GetLineCount) return subMxPluginPort_Cast_Text_GetLineCount(CastNumber, LangNum, Count);
	return false;
}

BOOL MxPluginPort_Cast_Text_GetLineString(int CastNumber, int LineNumber, int LangNum, void** Str)
{
	if (Str != NULL) *Str = NULL;
	if (subMxPluginPort_Cast_Text_GetLineString) return subMxPluginPort_Cast_Text_GetLineString(CastNumber, LineNumber, LangNum, Str);
	return false;
}

BOOL MxPluginPort_Cast_TextML_GetLanguageAssigned(int CastNumber, int LangNum, BOOL* Flag)
{
	if (Flag != NULL) *Flag = false;
	if (subMxPluginPort_Cast_TextML_GetLangAssigned) return subMxPluginPort_Cast_TextML_GetLangAssigned(CastNumber, LangNum, Flag);
	return false;
}

BOOL MxPluginPort_Cast_TextML_CreateLanguage(int CastNumber, int LangNum)
{
	if (subMxPluginPort_Cast_TextML_CreateLanguage) return subMxPluginPort_Cast_TextML_CreateLanguage(CastNumber, LangNum);
	return false;
}

BOOL MxPluginPort_Cast_TextML_RemoveLanguage(int CastNumber, int LangNum)
{
	if (subMxPluginPort_Cast_TextML_RemoveLanguage) return subMxPluginPort_Cast_TextML_RemoveLanguage(CastNumber, LangNum);
	return false;
}
