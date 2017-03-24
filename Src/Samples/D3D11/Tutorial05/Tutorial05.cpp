//--------------------------------------------------------------------------------------
// File: Tutorial05.cpp
//
// This application demonstrates animation using matrix transformations
//
// http://msdn.microsoft.com/en-us/library/windows/apps/ff729722.aspx
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "pch.h"
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"


using namespace DirectX;

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};


struct ConstantBuffer
{
    XMMATRIX mWorld;
    XMMATRIX mView;
    XMMATRIX mProjection;
};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE               g_hInst = nullptr;
HWND                    g_hWnd = nullptr;
D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*           g_pd3dDevice = nullptr;
ID3D11Device1*          g_pd3dDevice1 = nullptr;
ID3D11DeviceContext*    g_pImmediateContext = nullptr;
ID3D11DeviceContext1*   g_pImmediateContext1 = nullptr;
IDXGISwapChain*         g_pSwapChain = nullptr;
IDXGISwapChain1*        g_pSwapChain1 = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
ID3D11Texture2D*        g_pDepthStencil = nullptr;
ID3D11DepthStencilView* g_pDepthStencilView = nullptr;
ID3D11VertexShader*     g_pVertexShader = nullptr;
ID3D11PixelShader*      g_pPixelShader = nullptr;
ID3D11InputLayout*      g_pVertexLayout = nullptr;
ID3D11Buffer*           g_pVertexBuffer = nullptr;
ID3D11Buffer*           g_pIndexBuffer = nullptr;
ID3D11Buffer*           g_pConstantBuffer = nullptr;
XMMATRIX                g_World1;
XMMATRIX                g_World2;
XMMATRIX                g_View;
XMMATRIX                g_Projection;
UINT                    g_Width;
UINT                    g_Height;


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
HRESULT Resize(UINT width, UINT height);
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();


//--------------------------------------------------------------------------------------
// NoesisGUI
//--------------------------------------------------------------------------------------
#ifdef NOESIS_GUI

// All NoesisGUI API is under Noesis namespace
using namespace Noesis;

// This is the main view that displays the content
Ptr<Noesis::IView> g_XamlView;

// Error handler are invoked for fatal errors. You must never return from here
void NoesisErrorHandler(const NsChar* filename, NsSize line, const NsChar* desc, NsBool fatal)
{
    MessageBoxA(0, desc, "NoesisGUI Fatal Error", MB_ICONERROR);
}

// Map translation from windows keycodes to Noesis enums
Noesis::Key g_KeyMap[256];

void SetupKeyMap()
{
    memset(g_KeyMap, 0, sizeof(g_KeyMap));

    g_KeyMap[VK_BACK] = Key_Back;
    g_KeyMap[VK_TAB] = Key_Tab;
    g_KeyMap[VK_CLEAR] = Key_Clear;
    g_KeyMap[VK_RETURN] = Key_Return;
    g_KeyMap[VK_PAUSE] = Key_Pause;

    g_KeyMap[VK_SHIFT] = Key_LeftShift;
    g_KeyMap[VK_CONTROL] = Key_LeftCtrl;
    g_KeyMap[VK_MENU] = Key_LeftAlt;

    g_KeyMap[VK_ESCAPE] = Key_Escape;

    g_KeyMap[VK_SPACE] = Key_Space;
    g_KeyMap[VK_PRIOR] = Key_Prior;
    g_KeyMap[VK_NEXT] = Key_Next;
    g_KeyMap[VK_END] = Key_End;
    g_KeyMap[VK_HOME] = Key_Home;
    g_KeyMap[VK_LEFT] = Key_Left;
    g_KeyMap[VK_UP] = Key_Up;
    g_KeyMap[VK_RIGHT] = Key_Right;
    g_KeyMap[VK_DOWN] = Key_Down;
    g_KeyMap[VK_SELECT] = Key_Select;
    g_KeyMap[VK_PRINT] = Key_Print;
    g_KeyMap[VK_EXECUTE] = Key_Execute;
    g_KeyMap[VK_SNAPSHOT] = Key_Snapshot;
    g_KeyMap[VK_INSERT] = Key_Insert;
    g_KeyMap[VK_DELETE] = Key_Delete;
    g_KeyMap[VK_HELP] = Key_Help;

    g_KeyMap['0'] = Key_D0;
    g_KeyMap['1'] = Key_D1;
    g_KeyMap['2'] = Key_D2;
    g_KeyMap['3'] = Key_D3;
    g_KeyMap['4'] = Key_D4;
    g_KeyMap['5'] = Key_D5;
    g_KeyMap['6'] = Key_D6;
    g_KeyMap['7'] = Key_D7;
    g_KeyMap['8'] = Key_D8;
    g_KeyMap['9'] = Key_D9;

    g_KeyMap[VK_NUMPAD0] = Key_NumPad0;
    g_KeyMap[VK_NUMPAD1] = Key_NumPad1;
    g_KeyMap[VK_NUMPAD2] = Key_NumPad2;
    g_KeyMap[VK_NUMPAD3] = Key_NumPad3;
    g_KeyMap[VK_NUMPAD4] = Key_NumPad4;
    g_KeyMap[VK_NUMPAD5] = Key_NumPad5;
    g_KeyMap[VK_NUMPAD6] = Key_NumPad6;
    g_KeyMap[VK_NUMPAD7] = Key_NumPad7;
    g_KeyMap[VK_NUMPAD8] = Key_NumPad8;
    g_KeyMap[VK_NUMPAD9] = Key_NumPad9;

    g_KeyMap[VK_MULTIPLY] = Key_Multiply;
    g_KeyMap[VK_ADD] = Key_Add;
    g_KeyMap[VK_SEPARATOR] = Key_Separator;
    g_KeyMap[VK_SUBTRACT] = Key_Subtract;
    g_KeyMap[VK_DECIMAL] = Key_Decimal;
    g_KeyMap[VK_DIVIDE] = Key_Divide;

    g_KeyMap['A'] = Key_A;
    g_KeyMap['B'] = Key_B;
    g_KeyMap['C'] = Key_C;
    g_KeyMap['D'] = Key_D;
    g_KeyMap['E'] = Key_E;
    g_KeyMap['F'] = Key_F;
    g_KeyMap['G'] = Key_G;
    g_KeyMap['H'] = Key_H;
    g_KeyMap['I'] = Key_I;
    g_KeyMap['J'] = Key_J;
    g_KeyMap['K'] = Key_K;
    g_KeyMap['L'] = Key_L;
    g_KeyMap['M'] = Key_M;
    g_KeyMap['N'] = Key_N;
    g_KeyMap['O'] = Key_O;
    g_KeyMap['P'] = Key_P;
    g_KeyMap['Q'] = Key_Q;
    g_KeyMap['R'] = Key_R;
    g_KeyMap['S'] = Key_S;
    g_KeyMap['T'] = Key_T;
    g_KeyMap['U'] = Key_U;
    g_KeyMap['V'] = Key_V;
    g_KeyMap['W'] = Key_W;
    g_KeyMap['X'] = Key_X;
    g_KeyMap['Y'] = Key_Y;
    g_KeyMap['Z'] = Key_Z;

    g_KeyMap[VK_F1] = Key_F1;
    g_KeyMap[VK_F2] = Key_F2;
    g_KeyMap[VK_F3] = Key_F3;
    g_KeyMap[VK_F4] = Key_F4;
    g_KeyMap[VK_F5] = Key_F5;
    g_KeyMap[VK_F6] = Key_F6;
    g_KeyMap[VK_F7] = Key_F7;
    g_KeyMap[VK_F8] = Key_F8;
    g_KeyMap[VK_F9] = Key_F9;
    g_KeyMap[VK_F10] = Key_F10;
    g_KeyMap[VK_F11] = Key_F11;
    g_KeyMap[VK_F12] = Key_F12;
    g_KeyMap[VK_F13] = Key_F13;
    g_KeyMap[VK_F14] = Key_F14;
    g_KeyMap[VK_F15] = Key_F15;
    g_KeyMap[VK_F16] = Key_F16;
    g_KeyMap[VK_F17] = Key_F17;
    g_KeyMap[VK_F18] = Key_F18;
    g_KeyMap[VK_F19] = Key_F19;
    g_KeyMap[VK_F20] = Key_F20;
    g_KeyMap[VK_F21] = Key_F21;
    g_KeyMap[VK_F22] = Key_F22;
    g_KeyMap[VK_F23] = Key_F23;
    g_KeyMap[VK_F24] = Key_F24;

    g_KeyMap[VK_NUMLOCK] = Key_NumLock;
    g_KeyMap[VK_SCROLL] = Key_Scroll;
}
#endif


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (FAILED(InitWindow(hInstance, nCmdShow)))
        return 0;

    if (FAILED(InitDevice()))
    {
        CleanupDevice();
        return 0;
    }

#ifdef NOESIS_GUI
    {
        SetupKeyMap();

        // NoesisGUI is initialized here. Resources will be loaded from current working directory
        Noesis::GUI::Init(NoesisErrorHandler);
        Noesis::GUI::SetResourceProvider(".");

        // Loads XAML and creates a view with it
        Ptr<FrameworkElement> xaml = Noesis::GUI::LoadXaml<FrameworkElement>("PasswordBox.xaml");
        g_XamlView = Noesis::GUI::CreateView(xaml.GetPtr());
        g_XamlView->SetSize(g_Width, g_Height);
        g_XamlView->SetAntialiasingMode(Noesis::Gui::AntialiasingMode_PPAA);

        // Initializes renderer. This could be done in a render thread
        Ptr<RenderDevice> device = *new D3D11RenderDevice(g_pImmediateContext);
        Ptr<VGContext> context = Noesis::GUI::CreateVGContext(device.GetPtr(), Noesis::VGOptions());
        g_XamlView->GetRenderer()->Init(context.GetPtr());
    }
#endif

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            ::Render();
        }
    }

    CleanupDevice();

#ifdef NOESIS_GUI
    {
        // Free global resources and shutdown kernel
        g_XamlView.Reset();
        Noesis::GUI::Shutdown();
    }
#endif

    return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    g_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 5", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!g_hWnd)
        return E_FAIL;

    ShowWindow(g_hWnd, nCmdShow);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(g_hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);

        if (hr == E_INVALIDARG)
        {
            // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
            hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
        }

        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    // Obtain DXGI factory from device (since we used nullptr for pAdapter above)
    IDXGIFactory1* dxgiFactory = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = g_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                adapter->Release();
            }
            dxgiDevice->Release();
        }
    }
    if (FAILED(hr))
        return hr;

    // Create swap chain
    IDXGIFactory2* dxgiFactory2 = nullptr;
    hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // DirectX 11.1 or later
        hr = g_pd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&g_pd3dDevice1));
        if (SUCCEEDED(hr))
        {
            (void)g_pImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&g_pImmediateContext1));
        }

        DXGI_SWAP_CHAIN_DESC1 sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2->CreateSwapChainForHwnd(g_pd3dDevice, g_hWnd, &sd, nullptr, nullptr, &g_pSwapChain1);
        if (SUCCEEDED(hr))
        {
            hr = g_pSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&g_pSwapChain));
        }

        dxgiFactory2->Release();
    }
    else
    {
        // DirectX 11.0 systems
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = g_hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain(g_pd3dDevice, &sd, &g_pSwapChain);
    }

    dxgiFactory->Release();

    if (FAILED(hr))
        return hr;

    hr = Resize(width, height);
    if (FAILED(hr))
        return hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"Tutorial05.fx", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &g_pVertexLayout);
    pVSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Set the input layout
    g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"Tutorial05.fx", "PS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Create vertex buffer
    SimpleVertex vertices[] =
    {
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
    };
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * 8;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;
    hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
    if (FAILED(hr))
        return hr;

    // Set vertex buffer
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    // Create index buffer
    WORD indices[] =
    {
        3, 1, 0,
        2, 1, 3,

        0, 5, 4,
        1, 5, 0,

        3, 4, 7,
        0, 4, 3,

        1, 6, 5,
        2, 6, 1,

        2, 7, 6,
        3, 7, 2,

        6, 4, 5,
        7, 4, 6,
    };
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = indices;
    hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
    if (FAILED(hr))
        return hr;

    // Set index buffer
    g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    // Set primitive topology
    g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Create the constant buffer
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(ConstantBuffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pConstantBuffer);
    if (FAILED(hr))
        return hr;

    // Initialize the world matrix
    g_World1 = XMMatrixIdentity();
    g_World2 = XMMatrixIdentity();

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
    XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    g_View = XMMatrixLookAtLH(Eye, At, Up);

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Resize
//--------------------------------------------------------------------------------------
HRESULT Resize(UINT width, UINT height)
{
    HRESULT hr = S_OK;

    g_Width = width;
    g_Height = height;

    // // Release all outstanding references to the swap chain's buffers
    if (g_pDepthStencil) g_pDepthStencil->Release();
    if (g_pDepthStencilView) g_pDepthStencilView->Release();
    if (g_pRenderTargetView) g_pRenderTargetView->Release();

    g_pImmediateContext->OMSetRenderTargets(0, 0, 0);

    hr = g_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
    if (FAILED(hr))
        return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr))
        return hr;

    hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = g_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);
    if (FAILED(hr))
        return hr;

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil, &descDSV, &g_pDepthStencilView);
    if (FAILED(hr))
        return hr;

    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports(1, &vp);

    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / (FLOAT)height, 0.01f, 100.0f);

#ifdef NOESIS_GUI
    if (g_XamlView != 0)
    {
        g_XamlView->SetSize(g_Width, g_Height);
    }
#endif

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    if (g_pImmediateContext) g_pImmediateContext->ClearState();

    if (g_pConstantBuffer) g_pConstantBuffer->Release();
    if (g_pVertexBuffer) g_pVertexBuffer->Release();
    if (g_pIndexBuffer) g_pIndexBuffer->Release();
    if (g_pVertexLayout) g_pVertexLayout->Release();
    if (g_pVertexShader) g_pVertexShader->Release();
    if (g_pPixelShader) g_pPixelShader->Release();
    if (g_pDepthStencil) g_pDepthStencil->Release();
    if (g_pDepthStencilView) g_pDepthStencilView->Release();
    if (g_pRenderTargetView) g_pRenderTargetView->Release();
    if (g_pSwapChain1) g_pSwapChain1->Release();
    if (g_pSwapChain) g_pSwapChain->Release();
    if (g_pImmediateContext1) g_pImmediateContext1->Release();
    if (g_pImmediateContext) g_pImmediateContext->Release();
    if (g_pd3dDevice1) g_pd3dDevice1->Release();
    if (g_pd3dDevice) g_pd3dDevice->Release();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            if (g_pSwapChain)
            {
                RECT rc;
                GetClientRect(hWnd, &rc);
                Resize(rc.right - rc.left, rc.bottom - rc.top);
            }
            break;

#ifdef NOESIS_GUI
        case WM_KEYDOWN:
            if (g_XamlView != 0)
            {
                g_XamlView->KeyDown(wParam < 256 ? g_KeyMap[wParam] : Noesis::Key_None);
            }
            break;

        case WM_KEYUP:
            if (g_XamlView != 0)
            {
                g_XamlView->KeyUp(wParam < 256 ? g_KeyMap[wParam] : Noesis::Key_None);
            }
            break;

        case WM_CHAR:
            if (g_XamlView != 0)
            {
                g_XamlView->Char(NsUInt32(wParam));
            }
            break;

        case WM_MOUSEMOVE:
            if (g_XamlView != 0)
            {
                g_XamlView->MouseMove(LOWORD(lParam), HIWORD(lParam));
            }
            break;

        case WM_LBUTTONDOWN:
            if (g_XamlView != 0)
            {
                g_XamlView->MouseButtonDown(LOWORD(lParam), HIWORD(lParam), MouseButton_Left);
            }
            break;

        case WM_LBUTTONUP:
            if (g_XamlView != 0)
            {
                g_XamlView->MouseButtonUp(LOWORD(lParam), HIWORD(lParam), MouseButton_Left);
            }
            break;

        case WM_MOUSEWHEEL:
            if (g_XamlView != 0)
            {
                POINT point;
                point.x = LOWORD(lParam);
                point.y = HIWORD(lParam);
                ::ScreenToClient(hWnd, &point);

                g_XamlView->MouseWheel(point.x, point.y, GET_WHEEL_DELTA_WPARAM(wParam));
            }
            break;
#endif

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Update our time
    static float t = 0.0f;
    if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
    {
        t += (float)XM_PI * 0.0125f;
    }
    else
    {
        static ULONGLONG timeStart = 0;
        ULONGLONG timeCur = GetTickCount64();
        if (timeStart == 0)
            timeStart = timeCur;
        t = (timeCur - timeStart) / 1000.0f;
    }

    // 1st Cube: Rotate around the origin
    g_World1 = XMMatrixRotationY(t);

    // 2nd Cube:  Rotate around origin
    XMMATRIX mSpin = XMMatrixRotationZ(-t);
    XMMATRIX mOrbit = XMMatrixRotationY(-t * 2.0f);
    XMMATRIX mTranslate = XMMatrixTranslation(-4.0f, 0.0f, 0.0f);
    XMMATRIX mScale = XMMatrixScaling(0.3f, 0.3f, 0.3f);

    g_World2 = mScale * mSpin * mTranslate * mOrbit;

#ifdef NOESIS_GUI
    // Updates view passing global time
    g_XamlView->Update(t);

    // Performs rendering operations. Note that the renderer associated to a view is intended
    // to be used in the render thread. In this simple application it is the main thread
    Noesis::IRenderer* renderer = g_XamlView->GetRenderer();

    // Applies changes to the render tree
    renderer->UpdateRenderTree();

    // Renders offscreen textures. This step must be done before binding the main render target
    if (renderer->NeedsOffscreen())
    {
        renderer->RenderOffscreen();
    }

    // Restore state. This must be done per frame because NoesisGUI modifies the GPU state
    // TODO: improve this by adding a SaveState() and RestoreState() to D3D11RenderDevice
    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);
    g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
    g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    g_pImmediateContext->OMSetDepthStencilState(0, 0);
    g_pImmediateContext->RSSetState(0);
    g_pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);

    D3D11_VIEWPORT vp = { 0.0f, 0.0f, (FLOAT)g_Width, (FLOAT)g_Height, 0.0f, 1.0f};
    g_pImmediateContext->RSSetViewports(1, &vp);
#endif

    //
    // Clear the back buffer
    //
    g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, DirectX::Colors::MidnightBlue);

    //
    // Clear the depth buffer to 1.0 (max depth)
    //
    g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

    //
    // Update variables for the first cube
    //
    ConstantBuffer cb1;
    cb1.mWorld = XMMatrixTranspose(g_World1);
    cb1.mView = XMMatrixTranspose(g_View);
    cb1.mProjection = XMMatrixTranspose(g_Projection);
    g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb1, 0, 0);

    //
    // Render the first cube
    //
    g_pImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
    g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
    g_pImmediateContext->PSSetShader(g_pPixelShader, nullptr, 0);
    g_pImmediateContext->DrawIndexed(36, 0, 0);

    //
    // Update variables for the second cube
    //
    ConstantBuffer cb2;
    cb2.mWorld = XMMatrixTranspose(g_World2);
    cb2.mView = XMMatrixTranspose(g_View);
    cb2.mProjection = XMMatrixTranspose(g_Projection);
    g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb2, 0, 0);

    //
    // Render the second cube
    //
    g_pImmediateContext->DrawIndexed(36, 0, 0);


#ifdef NOESIS_GUI
    // Renders UI to active render target in the active viewport
    renderer->Render();
#endif

    //
    // Present our back buffer to our front buffer
    //
    g_pSwapChain->Present(0, 0);
}
