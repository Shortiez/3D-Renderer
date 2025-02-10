// App_TopBarUI.cpp

#include "App_TopBarUI.h"
#include "../core/SceneManager.h"
#include <imgui.h>

namespace BG3DRenderer::UI
{
    App_TopBarUI::App_TopBarUI() {
        // UI-specific style setup, if any (e.g., window padding, spacing)
        ImGui::GetStyle().WindowPadding = ImVec2(10, 10);
        ImGui::GetStyle().ItemSpacing = ImVec2(8, 8);
    }

    App_TopBarUI::~App_TopBarUI() {
        // No need to destroy the ImGui context here, as it's managed globally
    }

    void App_TopBarUI::Render() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::BeginMenu("Load Scene")) {
                    // Iterate over all defined demo scenes
                    for (const auto& sceneInfo : demoScenes) {
                        if (ImGui::MenuItem(sceneInfo.name.c_str())) {
                            // Load the selected scene via SceneManager
                            Core::SceneManager::GetInstance().LoadScene(sceneInfo.createFunc());
                        }
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
}