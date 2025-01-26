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

    void DebugProfilerUI::Render(Scene& scene, Renderer& renderer) {
        NewFrame();

        if (ImGui::Begin("Debug Profiler", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

            shared_ptr<Camera> camera = scene.GetCamera();

            // Camera Debug Section
            if (ImGui::CollapsingHeader("Camera Debug")) {
                ImGui::Text("Position: %.2f, %.2f, %.2f", camera->Position.x, camera->Position.y, camera->Position.z);
                ImGui::Text("Yaw: %.2f, Pitch: %.2f", camera->Yaw, camera->Pitch);
                ImGui::Text("Front: %.2f, %.2f, %.2f", camera->Front.x, camera->Front.y, camera->Front.z);
                ImGui::Text("Right: %.2f, %.2f, %.2f", camera->Right.x, camera->Right.y, camera->Right.z);
                ImGui::Text("Up: %.2f, %.2f, %.2f", camera->Up.x, camera->Up.y, camera->Up.z);
            }

            // Frame Data Section
            if (ImGui::CollapsingHeader("Frame Performance")) {
                ImGui::Text("Smoothed FPS: %.2f", renderer.GetSmoothedFPS());
                ImGui::Text("Min Frame Time: %.6f s", renderer.GetMinFrameTime());
                ImGui::Text("Max Frame Time: %.6f s", renderer.GetMaxFrameTime());
                ImGui::Text("Frame Time Variance: %.6f", renderer.GetFrameTimeVariance());
            }

            // Renderer Data Section
            if (ImGui::CollapsingHeader("Renderer Data")) {
                ImGui::Text("Meshes Rendered: %d", static_cast<int>(scene.GetSceneObjectCount()));

                for (size_t i = 0; i < scene.GetSceneObjectCount(); ++i) {
                    ImGui::Separator();
                    ImGui::Text("Mesh %zu", i);

                    //const shared_ptr<SceneObject> sceneObject = scene.GetSceneObject(i);
                    //glm::vec4 color = sceneObject.->GetColour();

                    //ImGui::ColorEdit4(("Color##" + std::to_string(i)).c_str(), glm::value_ptr(color), ImGuiColorEditFlags_NoInputs);
                }

                ImGui::Separator();

                /*
                bool wireframeEnabled = renderer.RenderMode == RenderingMode::Wireframe;
                if (ImGui::Checkbox("Wireframe Enabled", &wireframeEnabled)) {
                    renderer.SetRenderMode(wireframeEnabled ? RenderingMode::Wireframe : RenderingMode::Normal);
                }
                */
            }
        }
        ImGui::End();

        EndFrame();
    }



    void DebugProfilerUI::EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}