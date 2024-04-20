#pragma once

#include "fwd.hpp"
#include "gl/framebuffer.h"
#include "renderer/renderer.h"
#include "window.h"
#include <memory>

namespace Bess
{
  class Application
  {
  public:
    Application();
    ~Application();

    void run();
    void quit();

    bool isKeyPressed(int key);

  private:
    Window m_window;

    std::unique_ptr<Gl::FrameBuffer> m_framebuffer;
    std::shared_ptr<Renderer2D::Camera> m_camera;

  private:
    void drawUI();
    void drawScene();

    bool isCursorInViewport();
    glm::vec2 getViewportMousePos();

    // callbacks
  private:
    void onWindowResize(int w, int h);
    void onMouseWheel(double x, double y);
    void onKeyPress(int key);
    void onKeyRelease(int key);
    void onLeftMouse(bool pressed);
    void onRightMouse(bool pressed);
    void onMiddleMouse(bool pressed);
    void onMouseMove(double x, double y);

  private:
    std::unordered_map<int, bool> m_pressedKeys;
    bool m_leftMousePressed = false;
    bool m_rightMousePressed = false;
    bool m_middleMousePressed = false;

    glm::vec2 m_mousePos = {0, 0};
  };
} // namespace Bess
