/**
 *  DirectXWindow.cpp
 *  Purpose: Build a DirectX managed window.
 *
 *  @author Raul Butuc
 *  @version 1.0.1 07/03/2015
 */

#include "DirectXWindow.h"

namespace DirectXApplication {

  /**
   *  Call the base class constructor with the same parameters.
   *
   *  @param hInstance The current instance handler.
   *  @param ClientWidth The width of the client.
   *  @param ClientHeight The height of the client.
   *  @param AppTitle The title for the window.
   */
  DirectXWindow::DirectXWindow(HINSTANCE hInstance, UINT ClientWidth, UINT ClientHeight, string AppTitle) :
    Window(hInstance, ClientWidth, ClientHeight, AppTitle) {}

  /**
   *  Initialise the DirectX window.
   *
   *  @return The state after trying to initialise the window.
   */
  bool DirectXWindow::Init() {
    return Window::Init();
  }

  /**
   *  Update the DirectX window.
   *
   *  @param dt The period of time after which the window should update.
   */
  void DirectXWindow::Update(float dt) {
    // @TODO: Write the Update function, given delta t.
  }

  /**
   *  Render the DirectX window.
   *
   *  @param dt The period of time after which the window should render.
   */
  void DirectXWindow::Render(float dt) {
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);
    m_pSwapChain->Present(0, 0);
  }

  /**
   *  Default destructor.
   */
  DirectXWindow::~DirectXWindow() {}

}