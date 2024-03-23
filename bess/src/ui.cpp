#include "ui.h"

#include "glad/glad.h"
#include "gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

namespace Bess {
UIState UI::state{};

glm::vec2 UI::dPos = {-0.25, 0.25};
glm::vec2 UI::dSize = {0.5, 0.5};

void UI::draw() {
    begin();
    drawSettings();
    drawViewport();
    ImGui::Begin("Properties");
    ImGui::SliderFloat2("Pos", glm::value_ptr(dPos), -1.0f, 1.0f);
    ImGui::End();
    end();
}

void UI::setViewportTexture(GLuint64 texture) {
    state.viewportTexture = texture;
}

void UI::drawSettings() {
    // auto mainDockspaceId = ImGui::GetID("MainDockspace");
    // ImGui::SetNextWindowDockID(mainDockspaceId);
    ImGui::Begin("Settings");
    ImGui::Text("Camera Controls");
    ImGui::SliderFloat("Zoom", &state.cameraZoom, 0.1f, 2.0f);

    ImGui::SliderFloat2("Camera Pos", glm::value_ptr(state.cameraPos), -1.0f,
                        1.0f);
    ImGui::End();
}

void UI::drawViewport() {
    ImGuiWindowFlags flags =
        // ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Viewport", nullptr, flags);
    auto viewportPanelSize = ImGui::GetContentRegionAvail();
    if (viewportPanelSize.x != state.viewportSize.x ||
        viewportPanelSize.y != state.viewportSize.y) {
        state.viewportSize = {viewportPanelSize.x, viewportPanelSize.y};
    }

    ImGui::Image((void *)state.viewportTexture,
                 ImVec2(viewportPanelSize.x, viewportPanelSize.y), ImVec2(0, 1),
                 ImVec2(1, 0));
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

} // namespace Bess
