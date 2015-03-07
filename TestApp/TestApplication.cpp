#include "TestApplication.h"

namespace DirectXApplication {

	TestApplication::TestApplication(HINSTANCE hInstance) : Window(hInstance) {}

	bool TestApplication::Init() {
		return Window::Init();
	}

	void TestApplication::Update(float dt) {
		// @TODO: Create the Update function, given delta t.
	}

	void TestApplication::Render(float dt) {
		// @TODO: Create the Render function, given delta t.
	}

	TestApplication::~TestApplication() {}

}