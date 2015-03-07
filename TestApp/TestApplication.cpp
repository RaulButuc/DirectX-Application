#include "TestApplication.h"

namespace DirectXApplication {

	TestApplication::TestApplication(HINSTANCE hInstance) : Window(hInstance) {}

	bool TestApplication::Init() {
		return Window::Init();
	}

	void TestApplication::Update(float dt) {

	}

	void TestApplication::Render(float dt) {

	}

	TestApplication::~TestApplication() {}

}