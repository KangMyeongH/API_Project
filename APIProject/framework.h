#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <wincodec.h>
#include <dwrite.h>

// Direct3D 및 DXGI 헤더 파일 추가
#include <d3d11.h>
#include <dxgi1_2.h>
#include <d2d1_1helper.h>

// 라이브러리 링크
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
using namespace D2D1;

/*
 *IDWriteFactory* gWriteFactory;
ID3D11Device* gD3DDevice;
ID3D11DeviceContext* gD3DContext;
 */