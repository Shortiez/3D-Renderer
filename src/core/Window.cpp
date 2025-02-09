// Window.cpp
#include <glad/glad.h>
#include "Window.h"
#include <iostream>

namespace BG3DRenderer::Core {
    Window::Window(int width, int height, const char* title)
            : width(width), height(height) {
        if (!glfwInit()) {
            std::cerr << "GLFW initialization failed!" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE); // Enable Retina support
#endif

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // Get actual framebuffer size for proper viewport setup
        int framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        glViewport(0, 0, framebufferWidth, framebufferHeight);

        // Set the framebuffer callback
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

        glEnable(GL_DEPTH_TEST);
    }

    Window::~Window() {
        if (window) {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::SwapBuffers() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    float Window::GetAspectRatio() {
        int framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        return static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight);
    }

     void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }
}