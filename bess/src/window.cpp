extern "C" {
#include "glad/glad.h"
}
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.h"
#include <iostream>
#include <memory>

namespace Bess {
bool Window::isGLFWInitialized = false;
bool Window::isGladInitialized = false;
bool Window::isImguiInitialized = false;

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Window::Window(int width, int height, const std::string &title) {
    glfwSetErrorCallback(glfw_error_callback);

    this->initGLFW();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window =
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwSetWindowUserPointer(window, this);

    mp_window = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>(window);

    this->makeCurrent();

    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow *window, int w, int h) {
            auto this_ = (Window *)glfwGetWindowUserPointer(window);
            if (this_->m_callbacks.find(Callback::WindowResize) ==
                this_->m_callbacks.end())
                return;
            auto cb = std::any_cast<WindowResizeCallback>(
                this_->m_callbacks[Callback::WindowResize]);
            cb(w, h);
        });

    this->initOpenGL();
    this->initImgui();
}

void Window::initGLFW() {
    if (isGLFWInitialized)
        return;
    glfwInit();
    isGLFWInitialized = true;
}

void Window::initOpenGL() {
    if (isGladInitialized)
        return;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    } else {
        isGladInitialized = true;
    }
}

void Window::initImgui() {
    if (isImguiInitialized)
        return;
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable
    // Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(mp_window.get(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    isImguiInitialized = true;
    std::cout << "Initialized imgui" << std::endl;
}

Window::~Window() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    this->mp_window.reset();
    glfwTerminate();
}

void Window::update() const {
    makeCurrent();
    glfwSwapBuffers(mp_window.get());
}

void Window::makeCurrent() const { glfwMakeContextCurrent(mp_window.get()); }

bool Window::isClosed() const { return glfwWindowShouldClose(mp_window.get()); }

void Window::onWindowResize(WindowResizeCallback callback) {
    m_callbacks[Callback::WindowResize] = callback;
}

} // namespace Bess
