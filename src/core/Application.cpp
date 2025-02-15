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
              appInput(appWindow.GetWindow()),
              persistentAppCamera(new Camera()),
              imGuiManager(appWindow.GetWindow())// ✅ ImGui needs the window
    {
        std::cout << "Application created" << std::endl;

        appRenderer.SetCamera(persistentAppCamera.get());

        // Load the initial scene.
        SceneManager::GetInstance().LoadScene(
            std::make_unique<Demos::Scene_SpinningCube>(&appRenderer, persistentAppCamera.get(), &appInput)
        );

        SceneManager::GetInstance().RegisterSceneChangeCallback(
            [this](Scene* newScene) { this->OnSceneChanged(newScene); }
        );

        auto currentScene = SceneManager::GetInstance().GetCurrentScene();
        assert(currentScene != nullptr);

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

    // This method is called whenever a new scene gets loaded.
    void Application::OnSceneChanged(Scene* newScene) {
        GLFWwindow* win = appWindow.GetWindow();

        // Update the user pointer to the new scene so that input callbacks refer to it
        glfwSetWindowUserPointer(win, newScene);

        // Re-register the scene's specific input callbacks
        glfwSetScrollCallback(win, Scene::scroll_callback);
        glfwSetCursorPosCallback(win, Scene::mouse_callback);

        appRenderer.SetCamera(newScene->GetCamera());

        // Optionally, you might want to call newScene->Start() or perform other initializations.
        std::cout << "Scene changed. Updated window callbacks and user pointer." << std::endl;
    }

    int delayFrames;;
    void Application::Run() {
        while (!appWindow.ShouldClose()) {
            auto currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            DeltaTime = deltaTime;

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (appInput.IsKeyPressed(GLFW_KEY_P))
            {
                std::make_unique<Demos::Scene_LightRoom>(&appRenderer, persistentAppCamera.get(), &appInput);
            }

            if (appInput.IsKeyPressed(GLFW_KEY_K))
            {
                std::make_unique<Demos::Scene_SpinningCube>(&appRenderer, persistentAppCamera.get(), &appInput);
            }

            auto currentScene = SceneManager::GetInstance().GetCurrentScene();
            if (currentScene) {
                glfwSetWindowUserPointer(appWindow.GetWindow(), currentScene);

                currentScene->Update(deltaTime);
                appRenderer.Render();

                imGuiManager.NewFrame();

                topUI.Render();
                profilerUI.Render(appRenderer);

                imGuiManager.Render();
            }
            else{
                assert(currentScene == nullptr);
            }

            appWindow.SwapBuffers();
        }

        std::cout << "Application stopped" << std::endl;
    }
}