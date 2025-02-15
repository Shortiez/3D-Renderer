#include "../ui/DebugProfilerUI.h"

#include <sstream>

#include "../graphics/Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <../../third-party/imgui/imgui.h>
#include <../../third-party/imgui/imgui_impl_glfw.h>
#include <../../third-party/imgui/imgui_impl_opengl3.h>
#include "../core/Scene.h"
#include "../core/Camera.h"
#include "../core/SceneManager.h"

using namespace BG3DRenderer::Core;

namespace BG3DRenderer::UI
{
    DebugProfilerUI::DebugProfilerUI() {
        // Set up default ImGui style for side menu
        ImGui::GetStyle().WindowPadding = ImVec2(10, 10);
        ImGui::GetStyle().ItemSpacing = ImVec2(8, 8);
    }

    DebugProfilerUI::~DebugProfilerUI() {
    }

    void DebugProfilerUI::Render(Renderer& renderer)
    {
        auto currentScene = SceneManager::GetInstance().GetCurrentScene();

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
            auto camera = currentScene->GetCamera();

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
            ImGui::Text("Scene Objects Rendered: %d", currentScene->GetSceneObjectCount());

            for (size_t i = 0; i < currentScene->GetSceneObjectCount(); ++i) {
                ImGui::BeginChild(("Scene Object " + std::to_string(i)).c_str(), ImVec2(0, 100), true);
                const auto& obj = currentScene->GetSceneObject(i);
                ImGui::Text("Position: %.2f, %.2f, %.2f", obj.transform.position.x, obj.transform.position.y, obj.transform.position.z);
                ImGui::Text("Rotation: %.2f, %.2f, %.2f", obj.transform.rotation.x, obj.transform.rotation.y, obj.transform.rotation.z);
                ImGui::Text("Scale: %.2f, %.2f, %.2f", obj.transform.scale.x, obj.transform.scale.y, obj.transform.scale.z);
                ImGui::EndChild();
            }

            ImGui::Spacing();
            ImGui::Spacing();

            ImGui::TextUnformatted("Lights Data");
            ImGui::Separator();
            ImGui::Text("Scene Lights: %d", currentScene->GetSceneLightsCount());

            for (size_t i = 0; i < currentScene->GetSceneLightsCount(); ++i) {
                ImGui::BeginChild(("Light " + std::to_string(i)).c_str(), ImVec2(0, 100), true);
                const auto &light = currentScene->GetSceneLight(i);
                ImGui::Text("Position: %.2f, %.2f, %.2f", light->transform.position.x, light->transform.position.y,
                            light->transform.position.z);
                ImGui::Text("Rotation: %.2f, %.2f, %.2f", light->transform.rotation.x, light->transform.rotation.y,
                            light->transform.rotation.z);

                ImGui::Text("Intensity: %.2f", light->intensity);
                ImGui::Text("Ambient: %.2f, %.2f, %.2f", light->ambient.r, light->ambient.g, light->ambient.b);
                ImGui::Text("Diffuse: %.2f, %.2f, %.2f", light->diffuse.r, light->diffuse.g, light->diffuse.b);
                ImGui::Text("Specular: %.2f, %.2f, %.2f", light->specular.r, light->specular.g, light->specular.b);
                ImGui::EndChild();
            }

            // Get the type name from the current scene.
            std::string sceneTypeName = typeid(*SceneManager::GetInstance().GetCurrentScene()).name();
            // Set the maximum number of characters per line.
            const std::size_t lineLength = 80;
            std::ostringstream oss;
            // Break the string into multiple lines.
            for (std::size_t i = 0; i < sceneTypeName.size(); i += lineLength) {
                oss << sceneTypeName.substr(i, lineLength) << "\n";
            }
            // Use ImGui's TextWrapped to display the multi-line string.
            ImGui::TextWrapped("%s", oss.str().c_str());
            /*
            bool wireframeEnabled = renderer.RenderMode == RenderingMode::Wireframe;
            if (ImGui::Checkbox("Wireframe Enabled", &wireframeEnabled)) {
                renderer.SetRenderMode(wireframeEnabled ? RenderingMode::Wireframe : RenderingMode::Normal);
            }
            */
        }
        ImGui::End();
    }
}