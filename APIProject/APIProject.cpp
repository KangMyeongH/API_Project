// APIProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "APIProject.h"
#include "Core.h"
#include "ImageManager.h"
#include "RenderManager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND gHwnd;                                     // 전역 윈도우 핸들
IDWriteFactory* gWriteFactory = nullptr;
ID2D1Factory1* gFactory = nullptr;
IWICImagingFactory2* gWICFactory = nullptr;
ID2D1Device* gDevice = nullptr;
ID2D1DeviceContext* gDeviceContext = nullptr;
IDXGISwapChain* gSwapChain = nullptr;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gFactory);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_APIPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIPROJECT));

    MSG msg;
    msg.message = WM_NULL;

    // Core의 초기화를 수행합니다:
    // TODO : 여기에 코드를 입력합니다.
    Core::GetInstance().Init(gHwnd);

    ULONGLONG llTime = GetTickCount64();

    // 기본 메시지 루프입니다:
    while (true)
    {
        // 애플리케이션 루프입니다:
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message) break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        // Core의 루프입니다:
        else
        {
        	// TODO : 여기에 Core의 Progress 동작
            Core::GetInstance().Progress();
        }
    }

    gFactory->Release();

    CoUninitialize();

    return static_cast<int>(msg.wParam);
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName 	= nullptr; // MAKEINTRESOURCEW(IDC_APIPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rcWnd{ 0,0, WIN_WIDTH, WIN_HEIGHT };

   AdjustWindowRect(&rcWnd, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, 
							szTitle, 
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, 
							0, 
							rcWnd.right - rcWnd.left, 
							rcWnd.bottom - rcWnd.top, 
							nullptr, 
							nullptr, 
							hInstance, 
							nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   gHwnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        HRESULT hr = S_OK;
        RECT r;
        GetClientRect(hWnd, &r);
        UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        D3D_DRIVER_TYPE driverTypes[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
        };
        UINT countOfDriverTypes = ARRAYSIZE(driverTypes);
        DXGI_SWAP_CHAIN_DESC swapDescription;
        ZeroMemory(&swapDescription, sizeof(swapDescription));
        swapDescription.BufferDesc.Width = r.right - r.left;
        swapDescription.BufferDesc.Height = r.bottom - r.top;
        swapDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapDescription.BufferDesc.RefreshRate.Numerator = 60;
        swapDescription.BufferDesc.RefreshRate.Denominator = 1;
        swapDescription.SampleDesc.Count = 1;
        swapDescription.SampleDesc.Quality = 0;
        swapDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapDescription.BufferCount = 1;
        swapDescription.OutputWindow = hWnd;
        swapDescription.Windowed = TRUE;

        ID3D11Device* d3dDevice = nullptr;
        for (UINT driverTypeIndex = 0; driverTypeIndex < countOfDriverTypes; driverTypeIndex++) {
            hr = D3D11CreateDeviceAndSwapChain(
                nullptr,
                driverTypes[driverTypeIndex],
                nullptr,
                createDeviceFlags,
                nullptr,
                0,
                D3D11_SDK_VERSION,
                &swapDescription,
                &gSwapChain,
                &d3dDevice,
                nullptr,
                nullptr
            );

            if (SUCCEEDED(hr)) {
                break;
            }
            else if (d3dDevice) {
                d3dDevice->Release();
                d3dDevice = nullptr;
            }
        }

        IDXGIDevice* dxgiDevice = nullptr;
        if (SUCCEEDED(hr)) {
            hr = d3dDevice->QueryInterface(IID_PPV_ARGS(&dxgiDevice));
        }

        if (SUCCEEDED(hr)) {
            hr = gFactory->CreateDevice(
                dxgiDevice,
                &gDevice
            );
        }

        /*
        gFactory->CreateHwndRenderTarget(RenderTargetProperties(),
            HwndRenderTargetProperties(hWnd, SizeU(r.right, r.bottom)),
            &gRenderTarget);*/
        DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&gWriteFactory)
        );

        IDXGISurface* surface = nullptr;

        if (SUCCEEDED(hr)) {
            hr = gSwapChain->GetBuffer(
                0,
                IID_PPV_ARGS(&surface)
            );
        }

        ID2D1Bitmap1* bitmap = nullptr;
        if (SUCCEEDED(hr)) {
            FLOAT dpiX, dpiY;
            dpiX = (FLOAT)GetDpiForWindow(GetDesktopWindow());
            dpiY = dpiX;

            D2D1_BITMAP_PROPERTIES1 properties = D2D1::BitmapProperties1(
                D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
                D2D1::PixelFormat(
                    DXGI_FORMAT_B8G8R8A8_UNORM,
                    D2D1_ALPHA_MODE_IGNORE
                ),
                dpiX,
                dpiY
            );

            if (SUCCEEDED(hr)) {
                hr = gDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &gDeviceContext);
            }

            hr = gDeviceContext->CreateBitmapFromDxgiSurface(
                surface,
                &properties,
                &bitmap
            );
        }


        if (SUCCEEDED(hr)) {
            gDeviceContext->SetTarget(bitmap);
        }

        if (dxgiDevice) dxgiDevice->Release();
        if (surface) surface->Release();
        if (bitmap) bitmap->Release();
        if (d3dDevice) d3dDevice->Release();
    }
        break;

    case WM_KEYDOWN:
    {
        if (wParam == VK_ESCAPE)
        {
            DestroyWindow(hWnd);
            break;
        }
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
                /*case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;*/
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        ImageManager::GetInstance().Release();

        /*
        if (gRenderTarget != nullptr)
        {
            gRenderTarget->Release();
            gRenderTarget = nullptr;
        }*/
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}