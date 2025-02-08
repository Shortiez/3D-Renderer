#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "Application.h"
#include "Scene.h"
#include "Window.h"
#include "../graphics/Renderer.h"

using namespace BG3DRenderer::Graphics;

namespace BG3DRenderer::Core {

    Application::Application()
            : appWindow(1200, 960, "3D Window"),   // ✅ Initialize window first
              appRenderer(Renderer()), // ✅ Now shader exists before this line
              appScene(&appRenderer, &appInput),   // ✅ Scene needs Renderer and Input
              appInput(appWindow.GetWindow()),    // ✅ Input system needs the window
              profilerUI(appWindow.GetWindow())  // ✅ Profiler needs the window
    {
        std::cout << "Application created" << std::endl;

        glfwSetWindowUserPointer(appWindow.GetWindow(), &appScene);

        glfwSetScrollCallback(appWindow.GetWindow(), Scene::scroll_callback);
        glfwSetCursorPosCallback(appWindow.GetWindow(), Scene::mouse_callback);

        glfwSetInputMode(appWindow.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        deltaTime = 0;
        lastFrame = 0;
    }

    Application::~Application() {
        std::cout << "Application destroyed" << std::endl;
    }

    void Application::Run() {
        while (!appWindow.ShouldClose()) {
            auto currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render here
            appScene.Update(deltaTime);
            appScene.Render();

            profilerUI.Render(appScene, appRenderer);

            appWindow.SwapBuffers();
        }

        std::cout << "Application stopped" << std::endl;
    }
}