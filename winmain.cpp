#include "Window.h"
#include "TestApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	DirectXApplication::TestApplication tApp(hInstance);

	if (!tApp.Init()) {
		return 1;
	}

	return tApp.Run();
}