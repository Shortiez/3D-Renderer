#include "DebugProfilerUI.h"
#include "../graphics/Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../core/Scene.h"
#include "../core/Camera.h"

using namespace BG3DRenderer::Core;

namespace BG3DRenderer::Debug {
    DebugProfilerUI::DebugProfilerUI(GLFWwindow *window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");  // macOS uses OpenGL 4.1

        // Set up default ImGui style for side menu
        ImGui::GetStyle().WindowPadding = ImVec2(10, 10);
        ImGui::GetStyle().ItemSpacing = ImVec2(8, 8);
    }

    DebugProfilerUI::~DebugProfilerUI() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void DebugProfilerUI::NewFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void DebugProfilerUI::EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DebugProfilerUI::Render(Scene& scene, Renderer& renderer) {
        NewFrame();

        // Set upside menu window flags and size
        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

        // Position and size for side menu
        const float MENU_WIDTH = 250.0f;
        int display_w, display_h;
        glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(MENU_WIDTH, (float)display_h));

        if (ImGui::Begin("Debug Profiler", nullptr, window_flags)) {
            shared_ptr<Camera> camera = scene.GetCamera();

            // Camera Debug Section - Always visible
            ImGui::TextUnformatted("Camera Debug");
            ImGui::Separator();
            ImGui::Text("Position: %.2f, %.2f, %.2f", camera->Position.x, camera->Position.y, camera->Position.z);
            ImGui::Text("Yaw: %.2f, Pitch: %.2f", camera->Yaw, camera->Pitch);
            ImGui::Text("Front: %.2f, %.2f, %.2f", camera->Front.x, camera->Front.y, camera->Front.z);
            ImGui::Text("Right: %.2f, %.2f, %.2f", camera->Right.x, camera->Right.y, camera->Right.z);
            ImGui::Text("Up: %.2f, %.2f, %.2f", camera->Up.x, camera->Up.y, camera->Up.z);
            ImGui::Spacing();
            ImGui::Spacing();

            // Frame Performance Section - Always visible
            ImGui::TextUnformatted("Frame Performance");
            ImGui::Separator();
            ImGui::Text("Smoothed FPS: %.2f", renderer.GetSmoothedFPS());
            ImGui::Text("Min Frame Time: %.6f s", renderer.GetMinFrameTime());
            ImGui::Text("Max Frame Time: %.6f s", renderer.GetMaxFrameTime());
            ImGui::Text("Frame Time Variance: %.6f", renderer.GetFrameTimeVariance());
            ImGui::Spacing();
            ImGui::Spacing();

            // Renderer Data Section - Always visible
            ImGui::TextUnformatted("Renderer Data");
            ImGui::Separator();
            ImGui::Text("Meshes Rendered: %d", static_cast<int>(scene.GetSceneObjectCount()));

            for (size_t i = 0; i < scene.GetSceneObjectCount(); ++i) {
                ImGui::Text("Mesh %zu", i);
                // Mesh-specific data can be added here
                ImGui::Separator();
            }

            /*
            bool wireframeEnabled = renderer.RenderMode == RenderingMode::Wireframe;
            if (ImGui::Checkbox("Wireframe Enabled", &wireframeEnabled)) {
                renderer.SetRenderMode(wireframeEnabled ? RenderingMode::Wireframe : RenderingMode::Normal);
            }
            */
        }
        ImGui::End();

        EndFrame();
    }
}