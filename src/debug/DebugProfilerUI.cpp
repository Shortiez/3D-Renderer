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

   void DebugProfilerUI::Render(Scene& scene, Renderer& renderer)
    {
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
            ImGui::Text("Scene Objects Rendered: %d", scene.GetSceneObjectCount());

            for (size_t i = 0; i < scene.GetSceneObjectCount(); ++i) {
                ImGui::BeginChild(("Scene Object " + std::to_string(i)).c_str(), ImVec2(0, 100), true);
                const auto& obj = scene.GetSceneObject(i);
                ImGui::Text("Position: %.2f, %.2f, %.2f", obj.transform.position.x, obj.transform.position.y, obj.transform.position.z);
                ImGui::Text("Rotation: %.2f, %.2f, %.2f", obj.transform.rotation.x, obj.transform.rotation.y, obj.transform.rotation.z);
                ImGui::Text("Scale: %.2f, %.2f, %.2f", obj.transform.scale.x, obj.transform.scale.y, obj.transform.scale.z);
                ImGui::EndChild();
            }

            ImGui::Spacing();
            ImGui::Spacing();

            ImGui::TextUnformatted("Lights Data");
            ImGui::Separator();
            ImGui::Text("Scene Lights: %d", scene.GetSceneLightsCount());

            for (size_t i = 0; i < scene.GetSceneLightsCount(); ++i) {
                ImGui::BeginChild(("Light " + std::to_string(i)).c_str(), ImVec2(0, 100), true);
                const auto& light = scene.GetSceneLight(i);
                ImGui::Text("Position: %.2f, %.2f, %.2f", light.transform.position.x, light.transform.position.y, light.transform.position.z);
                ImGui::Text("Intensity: %.2f", light.intensity);
                ImGui::Text("Ambient: %.2f, %.2f, %.2f", light.ambient.r, light.ambient.g, light.ambient.b);
                ImGui::Text("Diffuse: %.2f, %.2f, %.2f", light.diffuse.r, light.diffuse.g, light.diffuse.b);
                ImGui::Text("Specular: %.2f, %.2f, %.2f", light.specular.r, light.specular.g, light.specular.b);
                ImGui::EndChild();
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