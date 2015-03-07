#pragma once

#include "Window.h"

namespace DirectXApplication {

	class TestApplication : public Window {

	public:
		TestApplication(HINSTANCE);
		bool Init() override;
		void Update(float) override;
		void Render(float) override;
		~TestApplication();

	};

}