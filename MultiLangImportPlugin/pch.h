// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef PCH_H
#define PCH_H

// プリコンパイルするヘッダーをここに追加します
#include "framework.h"

#define _CRTDBG_MAP_ALLOC
#include <UserEnv.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <Shlwapi.h>
#include <fileapi.h>
#include <Windows.h>

#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <codecvt>


#include "Const.h"
#include "Utils.h"
#include "TextData.h"
#include "SdkData.h"
#include "WriteData.h"
#include "MxPluginLib.h"
#include "dllmain.h"
#include "WrapperIf.h"
#include "DataAccessor.h"
#include "SingleLogger.h"
#include "UnicodeLogger.h"
#include "MultiLangTextController.h"

#endif //PCH_H
