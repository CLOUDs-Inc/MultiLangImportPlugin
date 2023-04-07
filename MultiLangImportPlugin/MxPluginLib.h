#ifndef	D_MXPLUGINLIB_H
#define	D_MXPLUGINLIB_H

#pragma once

typedef float MXPLUGIN_VALUE;
typedef struct _MXPLUGIN_VECTOR3D {
	float x;
	float y;
	float z;
} MXPLUGIN_VECTOR3D;

//===============================================
//MxPluginPort_System_GetSDKVersionで使用する定義
//===============================================
#define		gsv_EXEVersion	(0)		// EXEリソースのバージョン情報(64bit)を取得
#define		gsv_FuncVersion	(1)		// 0から始まるバージョン番号(32bit)を取得
typedef enum TSDKVersionList_t {
	svl_Unassigned = 0,
	svl_20160125 = 1,			// 2016.01.25版SDKの場合
	svl_20200100 = 2,			// 2020年01月版SDKの場合
	svl_20200300 = 3				// 2020年03月版SDKの場合
} TSDKVersionList;

//========================================
//MxPluginPort_System_AddMemuで使用する定義
//========================================
#define		am_Import				(0)
#define		am_Export				(1)
#define		am_Runtime				(2)
#define		am_RootScore			(3)
#define		am_SubScore				(4)
#define		am_AnyScore				(5)
#define		am_Tool_Root			(6)
#define		am_Tool_Plugin			(7)
#define		am_Event_SaveMXPFile	(0x100)
#define		am_Event_SaveProject	(0x100)
#define		am_Event_LoadProject	(0x101)
#define		am_Event_CloseProject	(0x102)
#define		am_Event_NewProject		(0x103)
#define		am_Event_CastRename		(0x200)
#define		am_Event_CastDelete		(0x201)
#define		am_When_Running			(0x20000000)
#define		am_When_Anytime			(0x40000000)
#define		am_PreEvent				(0x80000000)

//==========================================
//MxPluginPort_System_Progressで使用する定義
//==========================================
typedef enum TSetProgressCommand_t {
	spg_SetVisible = 0x00,
	spg_SetProgress = 0x01,
	spg_SetMaxValue = 0x02,
	spg_SetMessage = 0x03
} TSetProgressCommand;

//========================================
//MxPluginPort_Project_Initで使用する定義
//========================================
#define		pi_Blank		0			//完全にブランクのコンテンツ
#define		pi_ScoreOnly	1			//ルートスコアのみのコンテンツ
#define		pi_ScoreCast	2			//ルートスコアとカメラと環境光
#define		pi_NonDialog	0x80000000	//警告ダイアログを表示しない

//================================================
//MxPluginPort_Project_LoadCabinetで使用する定義
//================================================
#define		lc_Cast_OverWrite		0x00000001	//キャスト名が重複した場合、後からロードしたキャストで上書きする
#define		lc_Cast_Rename			0x00000002	//キャスト名が重複した場合、別名でロードする
#define		lc_Cast_UseOldRename	0x00000003	//キャスト名が重複した場合、既存のデータを使用し、別名でロードする
#define		lc_Cast_UseOldRelease	0x00000004	//キャスト名が重複した場合、既存のデータを使用し、キャビネット中のキャストは破棄する

#define		lc_Score_OverWrite		0x00010000	//スコア名が重複した場合、後からロードしたスコアで上書きする
#define		lc_Score_Rename			0x00020000	//スコア名が重複した場合、別名でロードする
#define		lc_Score_UseOldRelease	0x00040000	//スコア名が重複した場合、既存のデータを使用し、キャビネット中のスコアは破棄する

#define		lc_Track_SelectScoreNum 0x80000000	//MxPluginPort_Project_LoadCabinetEx専用:

//========================================
//MxPluginPort_Cast_CreateLightで使用する定義
//========================================
#define		lt_Directional	0			//平行光
#define		lt_Point		1			//点光源
#define		lt_Spot			2			//スポットライト
#define		lt_Ambient		3			//環境光

//========================================
//MxPluginPort_Track_GetFrameData,
//MxPluginPort_Track_SetFrameData,
//MxPluginPort_Track_Trimで使用する定義
//========================================
#define		fd_3DTrack		0x00		/*	TFD_3DTrackData	*/
#define		fd_CastNumber	0x01		/*	int				*/
#define		fd_2DPosition	0x02		/*	POINT			*/
#define		fd_Script		0x03		/*	int				*/
#define		fd_2DSize		0x04		/*	POINT			*/
#define		fd_2DAlpha		0x05		/*	int				*/
#define		fd_Filter		0x06		/*	int				*/
#define		fd_2DAngle		0x07		/*	float			*/

//========================================
//MxPluginPort_LoopTrack_GetValue,
//MxPluginPort_LoopTrack_SetValueで使用する定義
//========================================
typedef enum TLoopTrackData_t {
	ld_None = 0,				//何もない
	ld_Top = 1,				//ループ先端
	ld_Middle = 2,				//ループの中
	ld_End = 3,				//ループ終端
	ld_Single = 4				//１フレームの中でループ
} TLoopTrackData;

//========================================
//MxPluginPort_Track_SetAttribute,
//MxPluginPort_Track_GetAttributeで使用する定義
//========================================
#define		ta_TrackVisible 0			//トラックの可視・不可視
#define		ta_TrackCanEdit	1			//編集可能・不可能

//========================================
//キャストの型の定義
//========================================
#define		ct_Model		(0)				//モデル
#define		ct_Texture		(1)				//テクスチャ
#define		ct_Bitmap		(2)				//ビットマップ
#define		ct_Text			(3)				//テキスト
#define		ct_Wave			(4)				//効果音
#define		ct_Midi			(5)				//MIDI
#define		ct_Script		(6)				//スクリプト
#define		ct_Camera		(7)				//カメラ
#define		ct_Light		(8)				//ライト
#define		ct_Movie		(9)				//Movie
#define		ct_Subscore		(10)			//サブスコアトラック  (仮想キャスト)
#define		ct_Sound3D		(11)			//3DSound
#define		ct_WaveEx		(12)			//拡張Waveトラック	  (仮想キャスト)
#define		ct_Listener		(13)			//耳キャスト
#define		ct_MovieCtrl	(14)			//MovieI制御トラック	 (仮想キャスト)
#define		ct_Material		(15)			//マテリアルトラック  (仮想キャスト)
#define		ct_MovieBill	(16)			//ビルボードムービー  (仮想キャスト)
#define		ct_BilTexAnm	(17)			//ビルボードテクスチャのアニメーション	(仮想キャスト)
#define		ct_TexNumAnm	(18)			//モデルのテクスチャ番号のアニメーション  (仮想キャスト)
#define		ct_ModelWrap	(19)			//モデルのテクスチャマッピングのアニメーション	(仮想キャスト)
#define		ct_ModelNum		(20)			//モデル番号のアニメーション (仮想キャスト)
#define		ct_Transition	(21)			//トランジション (仮想キャスト)
#define		ct_TransForm	(ct_Transition)	//※名前変更
#define		ct_Procedural	(29)			//プロシージャーキャスト

//========================================
//3D座標情報を持つトラックのフレーム情報の定義
//========================================
#define		kfd_Position		0x01
#define		kfd_Rotate			0x02
#define		kfd_Scale			0x04
#define		kfd_Visible			0x08
#define		kfd_PositionSmooth	0x10
#define		kfd_RotateSmooth	0x20
#define		kfd_ScaleSmooth		0x40

typedef struct	tagFD_3DTrackData {
	MXPLUGIN_VECTOR3D	Position;	//キャストの座標//
	MXPLUGIN_VECTOR3D	Rotate;		//キャストの回転//
	MXPLUGIN_VECTOR3D	Scale;		//キャストのスケール//
	DWORD				KeyData;
} TFD_3DTrackData;

//========================================
//キャストのプロパティ制御
//========================================
#define c_Cast_OverwriteFlag		(0x80000000)

//モデルキャスト
#define c_Model_Texture				0x10	//テクスチャを割り当てる
#define MxCast_Model_SetTexture(CastNum_Model,GroupNum,MultiTexNum,CastNum_Tex) MxPluginPort_CastPropety_SetDataInt(ct_Model,CastNum_Model,c_Model_Texture,CastNum_Tex,GroupNum,MultiTexNum)

//テクスチャキャスト
#define cp_Texture_TransparentColor 0x10	//テクスチャの透過色 0x0000FF=赤  0x00FF00=緑 0xFF0000=青 不透明: -1

//ビットマップキャスト
typedef enum TBitmapPropertyType_t {
	cp_Bitmap_TransparentColor = 0x10,	//ビットマップの透過色 0x0000FF=赤	0x00FF00=緑 0xFF0000=青 不透明: -1
	cp_Bitmap_AlphaEnabled = 0x11,	//半透明昨機能を有効にする 0=無効 1=有効
	cp_Bitmap_FixSize = 0x12,	//サイズ固定モード	0=サイズ可変 1=サイズ固定
	cp_Bitmap_ClickEnabled = 0x13,	//クリック判定		0=OFF 1=ON
	cp_Bitmap_GhostMode = 0x14,	//ゴーストモード	0=OFF 1=ON
	cp_Bitmap_DelayLoad = 0x15,	//遅延読み込み		0=OFF 1=ON
	cp_Bitmap_Backward = 0x16,	//背景に配置		0=OFF 1=ON
	cp_Bitmap_StayOnRAM = 0x17,	//RAMに配置する		0=OFF 1=ON
	cp_Bitmap_Use16BitColor = 0x18,	//16bit bitmapを使用する	0=OFF 1=ON
	cp_Bitmap_Use32BitColor = 0x19,	//32bit bitmapを使用する	0=OFF 1=ON
	cp_Bitmap_PaletteLink = 0x1A,	//Palette link		キャスト番号
	cp_Bitmap_GetWidth = 0x1B,	//ビットマップキャストの幅
	cp_Bitmap_GetHeight = 0x1C	//ビットマップキャストの高さ
} TBitmapPropertyType;

BOOL MxCast_Bitmap_SetDataInt(int CastNumber, TBitmapPropertyType PropertyType, int Value);	//キャストのプロパティを設定する
BOOL MxCast_Bitmap_GetDataInt(int CastNumber, TBitmapPropertyType PropertyType, int* Value);	//キャストのプロパティを取得する

//テキストキャスト
typedef enum TTextPropertyType_t {
	cp_Text_FontColor = 0x10,	//テキストの文字の色 0x0000FF=赤  0x00FF00=緑 0xFF0000=青
	cp_Text_BackColor = 0x11,	//テキストの背景の色 0x0000FF=赤  0x00FF00=緑 0xFF0000=青
	cp_Text_FontHeight = 0x12,	//テキストで使用するフォントの高さ
	cp_Text_FontSize = 0x13,	//テキストで使用するフォントのサイズ
	cp_Text_FontStyle = 0x14,	//テキストで使用するフォントのスタイル(TTextFontStyleTypeを指定できる)
	cp_Text_FontName = 0x15,	//テキストで使用するフォントの名前(文字列へのポインタを指定)
	cp_Text_FontCharSet = 0x16,	//テキストで使用するフォントのキャラクタセット
	cp_Text_Transparent = 0x17,	//テキストの背景が透過するかどうかを指定 0=不透明 1=透明
	cp_Text_ItemDistance = 0x18,	//テキストの行間
	cp_Text_Backward = 0x19,	//ステージウィンドウで後方に配置するかを指定 0=前方に配置 1=後方に配置
	cp_Text_AlphaEnabled = 0x1A,	//半透明昨機能を有効にする 0=無効 1=有効
	cp_Text_CenterX = 0x1B,	//回転の中心位置 X 座標
	cp_Text_CenterY = 0x1C,	//回転の中心位置 Y 座標
	cp_Text_FixSize = 0x1D,	//サイズ固定モード 0=サイズ可変 1=サイズ固定
	cp_Text_TextData = 0x1E,	//テキストの内容を指定(文字列へのポインタを指定)
	cp_Text_GetWidth = 0x1F,	//テキストキャスト全体の幅
	cp_Text_GetHeight = 0x20,	//テキストキャスト全体の高さ
	cp_Text_StringEncode = 0x21,	//文字コード(TTextStringEncodeTypeを指定できる)
	cp_Text_Alignment = 0x22,	//テキストの配置(TTextAlignmentを指定できる)
	cp_Text_AlignmentWidth = 0x23,	//テキストを左寄せ・中央寄せ・右寄せにした際のテキスト幅
	cp_Text_ClickEnabled = 0x24,	//クリック判定		0=OFF 1=ON
	cp_Text_Antialias = 0x25	//アンチエイリアス	0=OFF 1=ON
} TTextPropertyType;

typedef enum TTextStringEncodeType_t {
	set_ANSI = 0x00,
	set_UTF = 0x01
} TTextStringEncodeType;

typedef enum TTextFontStyleType_t {
	fs_Regular = 0x00,	//通常文字
	fs_Bold = 0x01,	//太字
	fs_Italic = 0x02,	//斜体
	fs_BoldItalic = 0x03	//太字+斜体
} TTextFontStyleType;

typedef enum TTextAlignment_t {
	talign_None = 0x00,		//アライメント処理無し／アライメント強制指定なし
	talign_Center = 0x01,		//中央
	talign_Right = 0x02,		//右寄せ
	talign_Left = 0x03,		//左寄せ
	talign_Center_Default = 0x11,		//中央・デフォルト指定
	talign_Right_Default = 0x12,		//右寄せ・デフォルト指定
	talign_Left_Default = 0x13,		//左寄せ・デフォルト指定
	talign_Negate = 0x80		//アライメント継承打ち消し
} TTextAlignment;

BOOL MxCast_Text_SetDataInt(int CastNumber, TTextPropertyType PropertyType, int  Value);	//キャストのプロパティを設定する
BOOL MxCast_Text_GetDataInt(int CastNumber, TTextPropertyType PropertyType, int* Value);	//キャストのプロパティを取得する

//スクリプトキャスト
#define cp_Script_ScriptData		0x10	//スクリプトの内容を指定(文字列へのポインタを指定)
#define MxCast_Script_SetCode(CastNum,Value)			MxPluginPort_CastPropety_SetDataPtr (ct_Script,CastNum,cp_Script_ScriptData		,Value)
#define cp_Script_Encode			0x11
#define cp_Script_External			0x12

typedef enum TScriptEncodeType_t {
	script_encode_ANSI = 0x00,
	script_encode_UTF8 = 0x01,
	script_encode_UTF8_BOM = 0x02
} TScriptEncodeType;

typedef enum TScriptExternalFile_t {
	script_file_Internal = 0x00,
	script_file_External = 0x01
} TScriptExternalFile;


//ライトキャスト
#define cp_Light_Color				0x10	//ライトの色 0x0000FF=赤  0x00FF00=緑 0xFF0000=青
#define cp_Light_DropOffRateA		0x11	//ライトの減衰率A 0.0～100.0
#define cp_Light_DropOffRateB		0x12	//ライトの減衰率B 0.0～100.0
#define cp_Light_DropOffRateC		0x13	//ライトの減衰率C 0.0～1.0
#define cp_Light_Distance			0x14	//ライトの到達距離 0.0～∞
#define cp_Light_CutOffAngle		0x15	//ライトの内側の照射円錐の角度 0～M_PI
#define cp_Light_CutOffAnglePhi		0x16	//ライトの外側の照射円錐の角度 0～M_PI
#define cp_Light_LightChannels		0x17	//ライトのチャンネル
#define cp_Light_MaterialTrack		0x18	//マテリアルトラックの影響を受けるかどうか (0=影響を受けない 1=影響を受ける)

#define MxCast_Light_SetColor(CastNum,Value)			MxPluginPort_CastPropety_SetDataInt  (ct_Light,CastNum,cp_Light_Color			,Value)
#define MxCast_Light_SetDropOffRateA(CastNum,Value)		MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_DropOffRateA	,Value)
#define MxCast_Light_SetDropOffRateB(CastNum,Value)		MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_DropOffRateB	,Value)
#define MxCast_Light_SetDropOffRateC(CastNum,Value)		MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_DropOffRateC	,Value)
#define MxCast_Light_SetDistance(CastNum,Value)			MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_Distance		,Value)
#define MxCast_Light_SetCutOffAngle(CastNum,Value)		MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_CutOffAngle		,Value)
#define MxCast_Light_SetCutOffAnglePhi(CastNum,Value)	MxPluginPort_CastPropety_SetDataFloat(ct_Light,CastNum,cp_Light_CutOffAnglePhi	,Value)
#define MxCast_Light_SetLightChannels(CastNum,Value)	MxPluginPort_CastPropety_SetDataInt  (ct_Light,CastNum,cp_Light_LightChannels	,Value)
#define MxCast_Light_SetMaterialTrack(CastNum,Value)	MxPluginPort_CastPropety_SetDataInt  (ct_Light,CastNum,cp_Light_MaterialTrack	,Value)

#define MxCast_Light_GetColor(CastNum,Value)			MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_Color			,Value)
#define MxCast_Light_GetDropOffRateA(CastNum,Value)		MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_DropOffRateA		,Value)
#define MxCast_Light_GetDropOffRateB(CastNum,Value)		MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_DropOffRateB		,Value)
#define MxCast_Light_GetDropOffRateC(CastNum,Value)		MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_DropOffRateC		,Value)
#define MxCast_Light_GetDistance(CastNum,Value)			MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_Distance			,Value)
#define MxCast_Light_GetCutOffAngle(CastNum,Value)		MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_CutOffAngle		,Value)
#define MxCast_Light_GetCutOffAnglePhi(CastNum,Value)	MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_CutOffAnglePhi	,Value)
#define MxCast_Light_GetLightChannels(CastNum,Value)	MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_LightChannels	,Value)
#define MxCast_Light_GetMaterialTrack(CastNum,Value)	MxPluginPort_CastPropety_GetData(ct_Light,CastNum,cp_Light_MaterialTrack	,Value)

//========================================
//フォントのスタイル設定
//========================================
#define fs_BOLD						0x01
#define fs_ITALIC					0x02
#define fs_UNDERLINE				0x04
#define fs_STRIKEOUT				0x08

//========================================
//テクスチャを読み込む時のリサイズ設定
//========================================
#define tr_NONE						0x00
#define tr_NEAR						0x01
#define tr_ROUNDDOWN				0x02
#define tr_ROUNDUP					0x03

//========================================
//MxPluginPort_Score_ClearのOptionの定義
//========================================
#define	sc_Track					0x01
#define	sc_LoopTrack				0x02
#define	sc_FrameLabel				0x04

/*================================================*/
/* MxPluginPort_Cast_CreateScriptExのOptionの定義 */
/*================================================*/
#define	cse_Encode_ANSI				0x01
#define	cse_Encode_UTF8				0x02

/*===============================================*/
/* MxPluginPort_Project_CreateRuntimeFile の定義 */
/*===============================================*/
#define	crm_MXEFile					0x00

typedef struct TMx_Project_CreateRuntimeFile_MXEOption_t {
	int Size;
	int Options;
} TMx_Project_CreateRuntimeFile_MXEOption;

#define	pcr_MXEOption_HideSaveDialog	(0x80000000)
#define pcr_MXEOption_RecommendSetting	(0x40000000)


/*======================================*/
/* MxPluginPort_Project_LoadFile の定義 */
/*======================================*/
#define	lff_XML							(0x01)

//==========================================
//MxPluginPort_Score_SetAnnotationEncodeで使用する定義
//==========================================
typedef enum TAnnotationEncode_t {
	sae_ANSI = 0x00,
	sae_UTF16 = 0x01,
	sae_UNSET = 0xFFFFFFFF
} TAnnotationEncode;

//========================================
//サービス関数の定義
//========================================
typedef LRESULT(_cdecl* TMxWMCOPYDATAPROC)(HWND hWnd, UINT message, WPARAM wParam, COPYDATASTRUCT* cds);

BOOL MxPluginPort_System_GetSDKEXEVersion(unsigned long long int* Version);
BOOL MxPluginPort_System_GetSDKFuncVersion(TSDKVersionList* Version);

int	 MxPluginPort_System_AddMemu(HINSTANCE hinstDLL, char* Name, int Option, void* Reserved, void* UserParam);			//MxSDKのメニューに任意のメニューを追加する
HWND MxPluginPort_System_GetHWnd(void);																				//メインウィンドウのハンドルを取得
int  MxPluginPort_System_GetSDKLanguage(void);																				//起動しているSDKが英語版(0)か日本語版(1)を取得
BOOL MxPluginPort_System_MenuCaption(int hinstMenu, char* Caption);														//メニューの文字列を設定する
BOOL MxPluginPort_System_MenuEnabled(int hinstMenu, BOOL Enabled);														//メニューの有効/無効状態を設定する
BOOL MxPluginPort_System_MenuVisible(int hinstMenu, BOOL Visible);														//メニューの表示/非表示状態を設定する
BOOL MxPluginPort_System_Paint(void* Reserved);																	//コンテンツを更新した結果を表示に反映させる
BOOL MxPluginPort_System_ProcessMessages(void);																				//Windowsのプロセスメッセージを処理する(使用は要注意)
BOOL MxPluginPort_System_ProgressMsg(char* Msg);
BOOL MxPluginPort_System_Progress(TSetProgressCommand Command, int Param);											//プログレスウィンドウを制御する

BOOL MxPluginPort_System_AttachEvent(HINSTANCE hinstDLL, UINT msg, TMxWMCOPYDATAPROC lpWMCopyDataProc);					//イベントにアタッチする
BOOL MxPluginPort_System_TrimLabelName(char* Des, char* Sou);																//

BOOL MxPluginPort_Event_GetEventType(HINSTANCE hinstDLL, int* Type);													//発生したイベントの形式を取得する
BOOL MxPluginPort_Event_GetMXPFileName(HINSTANCE hinstDLL, char** FileName);												//
BOOL MxPluginPort_Event_GetPreEvent(HINSTANCE hinstDLL, BOOL* Flag);													//
BOOL MxPluginPort_Event_GetUIHandle(HINSTANCE hinstDLL, int* Handle);													//イベントの発生要因となったUIのハンドルを取得する

BOOL MxPluginPort_Event_Score_GetScoreTrack(HINSTANCE hinstDLL, int* ScoreNum, int* TrackNum);									//スコア(トラック)でイベントが発生した場合の、スコア番号・トラック番号を取得する
BOOL MxPluginPort_Event_Score_GetSelectedCount(HINSTANCE hinstDLL, int* SelectedCount);											//スコア(トラック)でイベントが発生した場合の、選択しているトラック数を取得する
BOOL MxPluginPort_Event_Score_GetSelectedTrack(HINSTANCE hinstDLL, int Index, int* TrackNum);										//スコア(トラック)でイベントが発生した場合の、選択しているトラック数を取得する

BOOL MxPluginPort_Event_Cast_GetCastType(HINSTANCE hinstDLL, int* CastType);												//キャスト系イベントでのキャストタイプ
BOOL MxPluginPort_Event_Cast_GetCastNumber(HINSTANCE hinstDLL, int* CastNumber);											//キャスト系イベントでのキャスト番号
BOOL MxPluginPort_Event_Cast_GetOldName(HINSTANCE hinstDLL, char** OldName);												//キャストのリネームイベントでの古いキャスト名
BOOL MxPluginPort_Event_Cast_GetNewName(HINSTANCE hinstDLL, char** NewName);												//キャストのリネームイベントでの新しいキャスト名

BOOL MxPluginPort_Project_Init(int InitMode);																		//コンテンツを初期化する
BOOL MxPluginPort_Project_LoadCabinet(char* FileName, int Mode);															//キャビネットファイルをロードする
BOOL MxPluginPort_Project_LoadCabinetEx(char* FileName, int Mode, int* ScoreNumber, int* TrackNumber);						//キャビネットファイルをロードする
BOOL MxPluginPort_Project_SetScreenSize(int width, int height);															//スクリーンサイズを設定する
char* MxPluginPort_Project_GetContentsPath(void);																				//現在のコンテンツのパスを取得する
char* MxPluginPort_Project_GetContentsName(void);																				//現在のコンテンツの名前を取得する
BOOL MxPluginPort_Project_GetContentsSaved(void);																				//コンテンツが保存されて、名前が確定しているかを取得する
BOOL MxPluginPort_Project_GetContentsChanged(void);																				//コンテンツが変更されているかを取得する
BOOL MxPluginPort_Project_SetContentsChanged(void);
BOOL MxPluginPort_Project_ClearContentsChanged(void);
BOOL MxPluginPort_Project_SaveContents(char* FileName);																	//コンテンツを保存する
BOOL MxPluginPort_Project_LoadContents(char* FileName);																	//コンテンツをロードする
BOOL MxPluginPort_Project_CreateRuntimeFile(char* FileName, int Format, void* Options);										//ランタイムファイルを作成する
BOOL MxPluginPort_Project_GetContentsRunning(void);																				//コンテンツが再生中かどうかを取得する
BOOL MxPluginPort_Project_LoadFile(char* FileName, int Format, void* Options);										//ファイルをロードする

BOOL MxPluginPort_CLang_GetEnabled(void);
BOOL MxPluginPort_CLang_GetPathSRC(char** FileName);																	// C言語ライブラリコンテンツのソースコードパスを取得する
BOOL MxPluginPort_CLang_GetPathEvent(char** FileName);																	// C言語ライブラリコンテンツのイベントソースコードパスを取得する
BOOL MxPluginPort_CLang_GetPathLib(char** FileName);																	// C言語ライブラリコンテンツのMXCPPLibパスを取得する
BOOL MxPluginPort_CLang_GetPathOBJ(char** FileName);																	// C言語ライブラリコンテンツのOBJファイルパスを取得する
BOOL MxPluginPort_CLang_GetFileNameConst(char** FileName);																	// C言語ライブラリコンテンツの定数ファイル名(キャスト番号、スコア番号等)を取得する
BOOL MxPluginPort_CLang_GetFileNameEventSource(char** FileName);																	// C言語ライブラリコンテンツのイベントソースファイル名を取得する
BOOL MxPluginPort_CLang_GetFileNameEventHeader(char** FileName);																	// C言語ライブラリコンテンツのイベントヘッダファイル名を取得する

int  MxPluginPort_Cast_FindBlank(int CastType);																		//空白キャストを検索する
int  MxPluginPort_Cast_FindBlankSince(int CastType, int CastNumber);														//任意番号以降の空白キャストを検索する
int  MxPluginPort_Cast_GetCastCount(int CastType);																		//キャストの数を取得する
int  MxPluginPort_Cast_CreateCamera(int CastNumber, char* CastName);													//カメラキャストを作成する
int  MxPluginPort_Cast_CreateLight(int CastNumber, char* CastName, int LightType);										//ライトキャストを作成する
BOOL MxPluginPort_Cast_Delete(int CastType, int CastNumber, int Reserved);											//キャストを削除する
BOOL MxPluginPort_Cast_UseCheck(int CastType, int CastNumber);														//キャストが使用されているかチェック
int  MxPluginPort_Cast_GetCastName(int CastType, int CastNumber, char* CastName, int NameLength);						//キャスト名を取得する
int  MxPluginPort_Cast_SetCastName(int CastType, int CastNumber, char* NewName, BOOL OverWrite);							//キャスト名を設定する
BOOL MxPluginPort_Cast_SaveToFile(int CastType, int CastNumbe, char* FileName, void* Reserved);							//キャストをファイルに保存する
int  MxPluginPort_Cast_FindCast(int CastType, char* CastName);														//キャストを文字列で検索する
int  MxPluginPort_Cast_CreateWave(int CastNumber, char* CastName, char* FileName, BOOL ExternalFile);					//Waveキャストを作成する
int  MxPluginPort_Cast_CreateText(int CastNumber, char* CastName);													//Textキャストを作成する
int  MxPluginPort_Cast_CreateScript(int CastNumber, char* CastName);													//スクリプトキャストを作成する
int  MxPluginPort_Cast_CreateScriptEx(int CastNumber, char* CastName, char* FileName, int Options, int Reserved);			//スクリプトキャストを作成する
int  MxPluginPort_Cast_CreateTexture(int CastNumber, char* CastName, char* FileName);										//Textureキャストを作成する
int  MxPluginPort_Cast_CreateTextureEx(int CastNumber, char* CastName, char* FileName, int Option, int Reserved);				//Textureキャストを作成する
int  MxPluginPort_Cast_CreateBitmap(int CastNumber, char* CastName, char* FileName);										//Bitmapキャストを作成する
BOOL MxPluginPort_Cast_Assigned(int CastType, int CastNumber);														//キャストが存在するか調査する
int  MxPluginPort_Cast_TrimCastName(int CastType, char* SourCastName, char* DestCastName, int NameLength);				//キャスト名をSDKで登録する名前に変換する
BOOL MxPluginPort_Cast_TrimFileName(int CastType, int CastNumber);														//ファイルパスをキャスト名を基にした名称に差し替える
BOOL MxPluginPort_Cast_Exchange(int CastType, int CastNumber1, int CastNumber2);									//キャスト番号を交換する

BOOL MxTest_PluginPort_Cast_TrimCastName(void);																				//

int  MxPluginPort_Score_GetScoreName(int ScoreNumber, char* ScoreName, int NameLength);									//スコア名を取得する
int  MxPluginPort_Score_GetScoreCount(void);																				//スコアの数を取得する
int  MxPluginPort_Score_GetTrackCount(int ScoreNumber);																	//トラックの数を取得する
int  MxPluginPort_Score_CreateScore(char* ScoreName, int* TrackNumber);													//新規スコアを作成する
int  MxPluginPort_Score_CreateTrack(int ScoreNumber, int CastType, int CastNumber);										//新規トラックを作成する
BOOL MxPluginPort_Score_DeleteTrack(int ScoreNumber, int TrackNumber, int Reserved);										//トラックを削除する
BOOL MxPluginPort_Score_Trim(int ScoreNumber);																	//トラックを整理する
int  MxPluginPort_Score_GetLength(int ScoreNumber);																	//スコアの長さを取得する
int  MxPluginPort_Score_Find(char* ScoreName);																	//スコアを文字列で検索
BOOL MxPluginPort_Score_UpdateLength(int ScoreNumber);																	//スコアの長さを更新する
BOOL MxPluginPort_Score_Exchange(int ScoreNumber, int Track1, int Track2);											//２つのトラックの内容を交換する
BOOL MxPluginPort_Score_DeleteScore(int ScoreNumber);																	//スコアを削除する
int  MxPluginPort_Score_GetLabelName(int ScoreNumber, int FrameNumber, char* LabelName, int NameLength);				//フレームラベル名を取得する
BOOL MxPluginPort_Score_SetLabelName(int ScoreNumber, int FrameNumber, char* LabelName, int Reserved);					//フレームラベル名を設定する
int  MxPluginPort_Score_GetLabelPosMax(int ScoreNumber);																	//フレームラベルの最後の位置を取得する
int  MxPluginPort_Score_FindFrameLabel(int ScoreNumber, char* LabelName);													//フレームラベルを検索する
BOOL MxPluginPort_Score_Clear(int ScoreNumber, int Options);														//スコアの内容を消去する
BOOL MxPluginPort_Score_MoveTrack(int ScoreNumber, int MoveTo, int MoveFrom);										//トラックをスコア内で移動する
BOOL MxTest_MxPluginPort_Score_Clear(void);

BOOL MxPluginPort_Score_SetAnnotationEncode(int ScoreNumber, TAnnotationEncode Encode);
BOOL MxPluginPort_Score_SetAnnotationData(int ScoreNumber, int Page, void* Annotation);
BOOL MxPluginPort_Score_GetAnnotationEncode(int ScoreNumber, TAnnotationEncode* Encode);
BOOL MxPluginPort_Score_GetAnnotationData(int ScoreNumber, int Page, void** Annotation);
BOOL MxPluginPort_Score_GetAnnotationCount(int ScoreNumber, int* Page);
BOOL MxPluginPort_Score_ClearAnnotation(int ScoreNumber, int Page);
int  MxPluginPort_Score_InsertAnnotationData(int ScoreNumber, int Page, void* Annotation);
BOOL MxPluginPort_Score_RemoveAnnotationData(int ScoreNumber, int Page);

BOOL MxPluginPort_Track_GetCastType(int ScoreNumber, int TrackNumber, int* CastType);									//トラックに割り当てられているキャストの型を取得する
BOOL MxPluginPort_Track_GetCastNumber(int ScoreNumber, int TrackNumber, int* CastNumber);									//トラックに割り当てられているキャストの番号を取得する
BOOL MxPluginPort_Track_SetCastNumber(int ScoreNumber, int TrackNumber, int CastNumber);									//トラックに割り当てられているキャストの番号を取得する
int  MxPluginPort_Track_GetLength(int ScoreNumber, int TrackNumber);													//トラックの長さを取得する
BOOL MxPluginPort_Track_GetParent(int ScoreNumber, int TrackNumber, int* ParentTrackNumber);							//トラックの親子関係を取得する
BOOL MxPluginPort_Track_TestSetParent(int ScoreNumber, int ParentTrack, int ChildTrack);									//トラックの親子関係を設定可能かどうかを調査する
BOOL MxPluginPort_Track_SetParent(int ScoreNumber, int ParentTrack, int ChildTrack);									//トラックの親子関係を設定する
BOOL MxPluginPort_Track_GetFrameData(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType, void* Data);			//フレームの内容を取得する
BOOL MxPluginPort_Track_SetFrameData(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType, void* Data);			//フレームの内容を設定する
BOOL MxPluginPort_Track_Trim(int ScoreNumber, int TrackNumber, int FrameNumber, int TrackType);					//トラックの内容を整理する
BOOL MxPluginPort_Track_Assigned(int ScoreNumber, int TrackNumber);													//トラックが割り当てられているか調査する
int  MxPluginPort_Track_FindBlank(int ScoreNumber);																	//空きトラックを検索する
BOOL MxPluginPort_Track_SetAttribute(int ScoreNumber, int TrackNumber, int AttrType, BOOL Value);							//トラックの属性を設定する
BOOL MxPluginPort_Track_GetAttribute(int ScoreNumber, int TrackNumber, int AttrType, BOOL* Value);						//トラックの属性を取得する
int  MxPluginPort_Track_GetLabelName(int ScoreNumber, int TrackNumber, char* LabelName, int NameLength);				//トラックラベル名を取得する
BOOL MxPluginPort_Track_SetLabelName(int ScoreNumber, int TrackNumber, char* LabelName, int Reserved);					//トラックラベル名を設定する
int  MxPluginPort_Track_FindTrackLabel(int ScoreNumber, char* LabelName);													//トラックラベルを検索する

int  MxPluginPort_LoopTrack_GetLength(int ScoreNumbe);																	//ループトラックの長さを取得する
BOOL MxPluginPort_LoopTrack_GetValue(int ScoreNumber, int FrameNumber, TLoopTrackData* Value);							//ループトラックのフレームの値を取得する
BOOL MxPluginPort_LoopTrack_SetValue(int ScoreNumber, int FrameNumber, TLoopTrackData Value);								//ループトラックのフレームの値を設定する
BOOL MxPluginPort_LoopTrack_Trim(int ScoreNumber);																	//ループトラックを整理する

BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value);						//キャストのプロパティを設定する
BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value1, int Value2);			//キャストのプロパティを設定する
BOOL MxPluginPort_CastPropety_SetDataInt(int CastType, int CastNumber, int PropertyType, int	 Value1, int Value2, int Value3);	//キャストのプロパティを設定する
BOOL MxPluginPort_CastPropety_SetDataPtr(int CastType, int CastNumber, int PropertyType, void* Value);							//キャストのプロパティを設定する
BOOL MxPluginPort_CastPropety_SetDataFloat(int CastType, int CastNumber, int PropertyType, float Value);							//キャストのプロパティを設定する

BOOL MxPluginPort_Script_GetEncode(int CastNumber, TScriptEncodeType* Value);
BOOL MxPluginPort_Script_GetExternal(int CastNumber, TScriptExternalFile* Value);

BOOL MxPluginPort_CastPropety_GetData(int CastType, int CastNumber, int PropertyType, void* Value);							//キャストのプロパティを設定する
#define MXVEV3 MXPLUGIN_VECTOR3D
BOOL MxPluginPort_Primitive_QuadPolygon(int CastNumber, char* CastName, MXVEV3 V1, MXVEV3 V2, MXVEV3 V3, MXVEV3 V4);			//四頂点ポリゴンを作成
#undef MXVEV3

extern "C"
{
	__declspec(dllexport) BOOL _cdecl MxPlugin_SetProcAddress(int ID, void* FuncAddr);

}

#endif	/* D_MXPLUGINLIB_H */
