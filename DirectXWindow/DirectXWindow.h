#pragma once

#include "Window.h"

namespace DirectXApplication {

	class DirectXWindow : public Window {

	public:
		DirectXWindow(HINSTANCE, UINT, UINT);
		DirectXWindow(HINSTANCE, UINT, UINT, string);
		bool Init() override;
		void Update(float) override;
		void Render(float) override;
		~DirectXWindow();

	};

}