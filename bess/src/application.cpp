#include "application.h"
#include "gl/utils.h"
#include "imgui.h"
#include "renderer/primitives/quad.h"
#include "renderer/renderer.h"
#include <iostream>

namespace Bess {
Application::Application() : m_window(800, 600, "Bess") {
    m_window.onWindowResize([](int w, int h) {
        // glViewport(0, 0, w, h);
    });
    m_renderer.init();
}

Application::~Application() { m_window.close(); }

void Application::drawUI() {

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

    ImGuiIO &io = ImGui::GetIO();
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, viewport->Size);

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");

    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Viewport");
    auto viewportPanelSize = ImGui::GetContentRegionAvail();
    if (viewportPanelSize.x != m_renderer.getFrameBufferSize().x ||
        viewportPanelSize.y != m_renderer.getFrameBufferSize().y) {
        m_renderer.resizeFrameBuffer(viewportPanelSize);
    }
    auto texture = m_renderer.getData();
    ImGui::Image((void *)texture,
                 ImVec2(viewportPanelSize.x, viewportPanelSize.y), ImVec2(0, 1),
                 ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::End();
}

void Application::drawScene() {
    m_renderer.beginScene();
    m_renderer.clear();
    m_renderer.quad();
    m_renderer.endScene();
}

void Application::run() {
    while (!m_window.isClosed()) {
        m_window.pollEvents();

        m_renderer.begin();
        drawUI();

        drawScene();
        m_renderer.end();
        m_window.update();
    }
}
void Application::quit() { m_window.close(); }

} // namespace Bess
