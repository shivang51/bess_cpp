#include "ui.h"

#include "glad/glad.h"
#include "gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <string>

namespace Bess {
UIState UI::state{};

glm::vec2 UI::dPos = {-0.25, 0.25};
glm::vec2 UI::dSize = {0.5, 0.5};

void UI::init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable
    // Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    float fontSize = 16.0f; // *2.0f;
    io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto/Roboto-Bold.ttf",
                                 fontSize);
    io.FontDefault = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/Roboto/Roboto-Regular.ttf", fontSize);

    setDarkThemeColors();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void UI::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::draw() {
    begin();
    ProjectExplorer();
    drawViewport();
    ImGui::Begin("Properties");
    ImGui::Text("Hovered Id: %d", state.hoveredId);
    if (state.selectedId > 0 &&
        state.components.find(state.selectedId) != state.components.end()) {
        auto &selectedEnt = state.components[state.selectedId];
        ImGui::Text("Selected Id: %d", state.selectedId);
        ImGui::SliderFloat2("Pos", glm::value_ptr(selectedEnt->getPosition()),
                            -1.0f, 1.0f);
    }
    ImGui::End();
    end();
}

void UI::setViewportTexture(GLuint64 texture) {
    state.viewportTexture = texture;
}

void UI::ProjectExplorer() {
    ImGui::Begin("Project Explorer");
    for (auto &[id, entity] : state.components) {
        if (ImGui::Selectable(("Gate " + std::to_string(id)).c_str(),
                              state.selectedId == id)) {
            state.selectedId = id;
        }
    }
    ImGui::End();
}

void UI::drawViewport() {
    ImGuiWindowFlags flags =
        // ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin("Viewport", nullptr, flags);
    auto offset = ImGui::GetCursorPos();

    auto viewportPanelSize = ImGui::GetContentRegionAvail();
    if (viewportPanelSize.x != state.viewportSize.x ||
        viewportPanelSize.y != state.viewportSize.y) {
        state.viewportSize = {viewportPanelSize.x, viewportPanelSize.y};
    }

    ImGui::Image((void *)state.viewportTexture,
                 ImVec2(viewportPanelSize.x, viewportPanelSize.y), ImVec2(0, 1),
                 ImVec2(1, 0));

    auto pos = ImGui::GetWindowPos();
    auto gPos = ImGui::GetMainViewport()->Pos;

    state.viewportPos = {pos.x - gPos.x + offset.x, pos.y - gPos.y + offset.y};

    ImGui::End();
    ImGui::PopStyleVar();
}

void UI::begin() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    const ImGuiViewport *viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |=
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    static bool p_open = true;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", &p_open, window_flags);
    ImGui::PopStyleVar();

    ImGui::PopStyleVar(2);
    auto mainDockspaceId = ImGui::GetID("MainDockspace");
    ImGui::DockSpace(mainDockspaceId, viewport->Size);
}

void UI::end() {
    ImGui::End();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void UI::setDarkThemeColors() {
    auto &colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};

    // Headers
    colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
    colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
    colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
}

} // namespace Bess
