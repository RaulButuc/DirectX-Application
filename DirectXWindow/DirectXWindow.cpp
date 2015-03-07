/**
 *  DirectXWindow.cpp
 *  Purpose: Build a DirectX managed window.
 *
 *  @author Raul Butuc
 *  @version 1.0.0 06/03/2015
 */

#include "DirectXWindow.h"

namespace DirectXApplication {
	
	DirectXWindow::DirectXWindow(HINSTANCE hInstance) : Window(hInstance) {}

	DirectXWindow::DirectXWindow(HINSTANCE hInstance, UINT ClientWidth, UINT ClientHeight, string AppTitle) :
		Window(hInstance, ClientWidth, ClientHeight, AppTitle) {}

	bool DirectXWindow::Init() {
		return Window::Init();
	}

	void DirectXWindow::Update(float dt) {
		// @TODO: Create the Update function, given delta t.
	}

	void DirectXWindow::Render(float dt) {
		// @TODO: Create the Render function, given delta t.
	}

	DirectXWindow::~DirectXWindow() {}

}