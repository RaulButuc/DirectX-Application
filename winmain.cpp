/**
 *  winmain.cpp
 *  Purpose: Run the application and test its functionality.
 *
 *  @author Raul Butuc
 *  @version 1.0.0 06/03/2015
 */

#include "DirectXWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	DirectXApplication::DirectXWindow DXApp(hInstance, 1280, 720, "DirectX11 Application");

	if (!DXApp.Init()) {
		return 1;
	}

	return DXApp.Run();
}