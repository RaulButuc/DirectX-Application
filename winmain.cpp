#include "DirectXWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	DirectXApplication::DirectXWindow tApp(hInstance, 800, 600, "DirectX11 Application");

	if (!tApp.Init()) {
		return 1;
	}

	return tApp.Run();
}