#include "DirectXWindow.h"

namespace DirectXApplication {
	
	DirectXWindow::DirectXWindow(HINSTANCE hInstance, UINT ClientWidth, UINT ClientHeight) :
		Window(hInstance, ClientWidth, ClientHeight) {}

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