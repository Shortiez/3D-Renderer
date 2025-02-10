#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "Application.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"
#include "../../demos/demo_SpinningCube/Scene_SpinningCube.h"
#include "../graphics/Renderer.h"
#include "../ui/App_TopBarUI.h"

using namespace BG3DRenderer::Graphics;

namespace BG3DRenderer::Core {

    float Application::DeltaTime = 0;

    Application::Application()
            : appWindow(1200, 960, "3D Window"),   // ✅ Initialize window first
              appRenderer(Renderer()), // ✅ Now shader exists before this line
              appInput(appWindow.GetWindow()),    // ✅ Input system needs the window
              imGuiManager(appWindow.GetWindow()) // ✅ ImGui needs the window
    {
        std::cout << "Application created" << std::endl;

        SceneManager::GetInstance().LoadScene(
            std::make_unique<Demos::LightRoom::Scene_LightRoom>(&appRenderer, &appInput)
            );

        auto currentScene = SceneManager::GetInstance().GetCurrentScene();
        if (!currentScene) {
            std::cerr << "Error: current scene is null!" << std::endl;
            return;
        }

        currentScene->Init(&appRenderer, &appInput);
        glfwSetWindowUserPointer(appWindow.GetWindow(), currentScene);

        glfwSetScrollCallback(appWindow.GetWindow(), Scene::scroll_callback);
        glfwSetCursorPosCallback(appWindow.GetWindow(), Scene::mouse_callback);

        glfwSetInputMode(appWindow.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetInputMode(appWindow.GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        deltaTime = 0;
        lastFrame = 0;

        DeltaTime = 0;
    }

    Application::~Application() {
        std::cout << "Application destroyed" << std::endl;
    }

    void Application::Run() {
        while (!appWindow.ShouldClose()) {
            auto currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            DeltaTime = deltaTime;

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            auto currentScene = SceneManager::GetInstance().GetCurrentScene();
            if (currentScene) {
                glfwSetWindowUserPointer(appWindow.GetWindow(), currentScene);

                currentScene->Init(&appRenderer, &appInput);

                currentScene->Update(deltaTime);
                appRenderer.Render(*currentScene);

                imGuiManager.NewFrame();

                topUI.Render();
                profilerUI.Render(*currentScene, appRenderer);

                imGuiManager.Render();
            }
            appWindow.SwapBuffers();
        }

        std::cout << "Application stopped" << std::endl;
    }
}