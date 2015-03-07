/**
 *  Window.cpp
 *  Purpose: Build a DirectX supported WIN32 window.
 *
 *  @author Raul Butuc
 *  @version 1.0.2 07/03/2015
 */

#include "Window.h"

namespace DirectXApplication {

  // Used to forward messages to user defined procedure fuction.
  Window* g_pApp = nullptr;

  /**
   *  Constructor for a window.
   *
   *  @param hInstance The current instance handler.
   *  @param ClientWidth The width of the client.
   *  @param ClientHeight The height of the client.
   *  @param AppTitle The title for the window.
   */
  Window::Window(HINSTANCE hInstance, UINT ClientWidth, UINT ClientHeight, string AppTitle) {
    m_hAppInstance = hInstance;
    m_hAppWnd = NULL;
    m_ClientWidth = ClientWidth;
    m_ClientHeight = ClientHeight;
    m_AppTitle = AppTitle;
    m_WndStyle = WS_OVERLAPPEDWINDOW;
    g_pApp = this;

    m_pDevice = nullptr;
    m_pImmediateContext = nullptr;
    m_pRenderTargetView = nullptr;
    m_pSwapChain = nullptr;
  }

  /**
   *  Run the window and fetch the window message as long as not being told otherwise.
   *
   *  @return An integer representing the state
   */
  int Window::Run() {
    MSG msg = { 0 };

    while (WM_QUIT != msg.message) {
      if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
      else {
        Update(0.0f);
        Render(0.0f);
      }
    }

    return static_cast<int>(msg.wParam);
  }

  /**
   *  Framework method that initialises the window.
   *
   *  @return A boolean representing the success/failure state received after executing the init methods.
   */
  bool Window::Init() {
    // Initialise window.
    if (!InitWindow()) {
      return false;
    }

    // Initialise DirectX window.
    if (!InitDirect3D()) {
      return false;
    }

    return true;
  }

  /**
   *  Windows message procedure method.
   *
   *  @param hwnd Current window handler.
   *  @param msg The windows message.
   *  @param wParam A message parameter.
   *  @param lParam A message parameter.
   *  @return A long pointer, either nullptr or the result obtained from the default window procedure.
   */
  LRESULT Window::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
      case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

      default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
  }

  /**
   *  Windows callback message procedure method.
   *
   *  @param hwnd Current window handler.
   *  @param msg The windows message.
   *  @param wParam A message parameter.
   *  @param lParam A message parameter.
   *  @return A long pointer, either nullptr or the result obtained from the default window procedure.
   */
  LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (g_pApp) {
      return g_pApp->MsgProc(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
  }

  /**
   *  Destructor. Deallocate all the memory used.
   */
  Window::~Window() {
    if (m_pImmediateContext) {
      m_pImmediateContext->ClearState();
    }

    MemoryManagement::SafeRelease(m_pRenderTargetView);
    MemoryManagement::SafeRelease(m_pSwapChain);
    MemoryManagement::SafeRelease(m_pImmediateContext);
    MemoryManagement::SafeRelease(m_pDevice);
  }

  /**
   *  First part of the main framework method that initialises the application window.
   *  Deals with the main window display part.
   *
   *  @return A boolean representing the success/failure state received after attempting to initialise the window.
   */
  bool Window::InitWindow() {
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));

    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = m_hAppInstance;
    wcex.lpfnWndProc = MainWndProc;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = StringConverter<LPCWSTR, string>::convert("DXAPPWNDCLASS");;

    if (!RegisterClassEx(&wcex)) {
      OutputDebugString(StringConverter<LPCWSTR, string>::convert("Failed to create window class\n"));

      return false;
    }

    RECT rectangle = { 0, 0, m_ClientWidth, m_ClientHeight };
    AdjustWindowRect(&rectangle, m_WndStyle, FALSE);
    UINT width = rectangle.right - rectangle.left;
    UINT height = rectangle.bottom - rectangle.top;

    UINT xCoord = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
    UINT yCoord = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

    LPCWSTR lpClassName = StringConverter<LPCWSTR, string>::convert("DXAPPWNDCLASS");
    LPCWSTR lpWindowName = StringConverter<LPCWSTR, string>::convert(m_AppTitle);

    m_hAppWnd = CreateWindow(lpClassName, lpWindowName, m_WndStyle,
      xCoord, yCoord, width, height, NULL, NULL, m_hAppInstance, NULL);

    if (!m_hAppWnd) {
      OutputDebugString(StringConverter<LPCWSTR, string>::convert("Failed to create window\n"));

      return false;
    }

    ShowWindow(m_hAppWnd, SW_SHOW);

    return true;
  }

  /**
   *  Second part of the main framework method that initialises the application window.
   *  Deals with the DirectX display part.
   *
   *  @return A boolean representing the success/failure state received after attempting to initialise the window.
   */
  bool Window::InitDirect3D() {
    UINT createDeviceFlags = 0;

    #ifdef _DEBUG
      createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    #endif

    D3D_DRIVER_TYPE driverTypes[] = {
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_WARP,
      D3D_DRIVER_TYPE_REFERENCE
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] = {
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC swapDesc;
    ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
    swapDesc.BufferCount = 1;
    swapDesc.BufferDesc.Width = m_ClientWidth;
    swapDesc.BufferDesc.Height = m_ClientHeight;
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.OutputWindow = m_hAppWnd;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapDesc.Windowed = true;
    swapDesc.SampleDesc.Count = 1;
    swapDesc.SampleDesc.Quality = 0;
    swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    HRESULT result;
    for (int id = 0; id < numDriverTypes; ++id) {
      result = D3D11CreateDeviceAndSwapChain(NULL, driverTypes[id], NULL, createDeviceFlags,
        featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &swapDesc, &m_pSwapChain, &m_pDevice,
        &m_FeatureLevel, &m_pImmediateContext);

      if (SUCCEEDED(result)) {
        m_DriverType = driverTypes[id];
        break;
      }
    }

    if (FAILED(result)) {
      OutputDebugString(StringConverter<LPCWSTR, string>::convert("Failed to create device and swap chain."));

      return false;
    }

    ID3D11Texture2D* m_pBackBufferTex = 0;
    m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackBufferTex));
    m_pDevice->CreateRenderTargetView(m_pBackBufferTex, nullptr, &m_pRenderTargetView);

    m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

    m_Viewport.Width = static_cast<float>(m_ClientWidth);
    m_Viewport.Height = static_cast<float>(m_ClientHeight);
    m_Viewport.TopLeftX = 0;
    m_Viewport.TopLeftY = 0;
    m_Viewport.MinDepth = 0.0f;
    m_Viewport.MaxDepth = 1.0f;

    m_pImmediateContext->RSSetViewports(1, &m_Viewport);

    return true;
  }

}