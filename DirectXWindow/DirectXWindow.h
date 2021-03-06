/**
 *  DirectXWindow.h
 *  Purpose: Build a DirectX managed window.
 *
 *  @author Raul Butuc
 *  @version 1.0.1 07/03/2015
 */

#pragma once

#include "Window.h"

namespace DirectXApplication {

  class DirectXWindow : public Window {

    public:
      DirectXWindow(HINSTANCE, UINT, UINT, string);
      bool Init() override;
      void Update(float) override;
      void Render(float) override;
      ~DirectXWindow();

  };

}