#pragma once

#include <GLFW/glfw3.h>
#include <any>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace Bess {

enum Callback {
    WindowResize,
    MouseWheel,
};

typedef std::function<void(int, int)> WindowResizeCallback;
typedef std::function<void(double, double)> MouseWheelCallback;

class Window {
  public:
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow *window) { glfwDestroyWindow(window); }
    };

    Window(int width, int height, const std::string &title);
    ~Window();

    void update() const;
    void makeCurrent() const;
    bool isClosed() const;
    void close() const;

    inline void pollEvents() const { glfwWaitEvents(); }

    static bool isGLFWInitialized;
    static bool isGladInitialized;
    static bool isImguiInitialized;

    void onWindowResize(WindowResizeCallback callback);
    void onMouseWheel(MouseWheelCallback callback);

  private:
    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> mp_window;
    std::unordered_map<Callback, std::any> m_callbacks;

    void initImgui();
    void initOpenGL();
    void initGLFW();
};
} // namespace Bess
