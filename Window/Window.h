/**
 *  Window.h
 *  Purpose: Build a DirectX supported WIN32 window.
 *
 *  @author Raul Butuc
 *  @version 1.0.2 07/03/2015
 */

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include "StringConverter.h"
#include "DirectXUtilities.h"

using StringHelper::StringConverter;

namespace DirectXApplication {

	class Window {

		public:
			Window(HINSTANCE, UINT, UINT, string);
			int Run();
			virtual bool Init();
			virtual void Update(float) = 0;
			virtual void Render(float) = 0;
			virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
			virtual ~Window();

		protected:
			// Win32 attributes declaration.
			HWND		m_hAppWnd;
			HINSTANCE	m_hAppInstance;
			UINT		m_ClientWidth;
			UINT		m_ClientHeight;
			string		m_AppTitle;
			DWORD		m_WndStyle;

			// DirectX11 attributes declaration.
			ID3D11Device*				m_pDevice;
			ID3D11DeviceContext*		m_pImmediateContext;
			IDXGISwapChain*				m_pSwapChain;
			ID3D11RenderTargetView*		m_pRenderTargetView;
			D3D_DRIVER_TYPE				m_DriverType;
			D3D_FEATURE_LEVEL			m_FeatureLevel;
			D3D11_VIEWPORT				m_Viewport;

			// Win32 init fuction.
			bool InitWindow();

			// DirectX11 init function.
			bool InitDirect3D();
	};

}