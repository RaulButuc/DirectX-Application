/**
 *  Window.cpp
 *  Purpose: Build a standard WIN32 window.
 *
 *  @author Raul Butuc
 *  @version 1.0.0 06/03/2015
 */

#include "Window.h"

namespace DirectXApplication {

	Window* g_pApp = nullptr;

	Window::Window(HINSTANCE hInstance) {
		m_hAppInstance = hInstance;
		m_hAppWnd = NULL;
		m_ClientWidth = 800;
		m_ClientHeight = 600;
		m_AppTitle = "Title";
		m_WndStyle = WS_OVERLAPPEDWINDOW;
		g_pApp = this;
	}

	Window::Window(HINSTANCE hInstance, UINT ClientWidth, UINT ClientHeight, string AppTitle) {
		m_hAppInstance = hInstance;
		m_hAppWnd = NULL;
		m_ClientWidth = ClientWidth;
		m_ClientHeight = ClientHeight;
		m_AppTitle = AppTitle;
		m_WndStyle = WS_OVERLAPPEDWINDOW;
		g_pApp = this;
	}

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

	bool Window::Init() {
		return InitWindow();
	}

	LRESULT Window::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}

	LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if (g_pApp) {
			return g_pApp->MsgProc(hwnd, msg, wParam, lParam);
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	Window::~Window() {}

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

}