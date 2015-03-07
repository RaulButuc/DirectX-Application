#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include "StringConverter.h"

using StringHelper::StringConverter;

namespace DirectXApplication {

	class Window {

	public:
		Window(HINSTANCE, UINT, UINT);
		Window(HINSTANCE, UINT, UINT, string);
		int Run();
		virtual bool Init();
		virtual void Update(float) = 0;
		virtual void Render(float) = 0;
		virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
		virtual ~Window();

	protected:
		HWND		m_hAppWnd;
		HINSTANCE	m_hAppInstance;
		UINT		m_ClientWidth;
		UINT		m_ClientHeight;
		string		m_AppTitle;
		DWORD		m_WndStyle;

		bool InitWindow();

	};

}