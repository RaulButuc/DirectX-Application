#pragma once

#include "Window.h"

namespace DirectXApplication {

	class TestApplication : public Window {

	public:
		TestApplication(HINSTANCE);
		bool Init() override;
		void Update(float dt) override;
		void Render(float dt) override;
		~TestApplication();

	};

}