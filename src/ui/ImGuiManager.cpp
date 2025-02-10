// ImGuiManager.cpp

#include "ImGuiManager.h"

namespace BG3DRenderer::UI{
    ImGuiManager::ImGuiManager(GLFWwindow* window) {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        const char* glsl_version = "#version 330"; // Adjust GLSL version as needed
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void ImGuiManager::NewFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiManager::Render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ImGuiManager::~ImGuiManager() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}