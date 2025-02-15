//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "../graphics/Renderer.h"
#include "../core/Scene.h"
#include "Input.h"
#include "SceneManager.h"
#include "../ui/DebugProfilerUI.h"
#include "../ui/App_TopBarUI.h"
#include "../ui/ImGuiManager.h"

using namespace glm;

namespace BG3DRenderer::Core {
    class Application {
    private:
        Window appWindow;
        Renderer appRenderer;
        Input appInput;

        unique_ptr<Camera> persistentAppCamera;

        UI::ImGuiManager imGuiManager;
        UI::DebugProfilerUI profilerUI;
        UI::App_TopBarUI topUI;

        float deltaTime;
        float lastFrame;

        void OnSceneChanged(Scene* newScene);
    public:
        Application();
        ~Application();

        void Run();

        static float DeltaTime;
    };
}


#endif //APPLICATION_H
