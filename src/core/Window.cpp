//
// Created by Ben Gotts on 25/01/2025.
//

#include <glad/glad.h>
#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.h"

namespace BG3DRenderer::Core {
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    Window::Window(int width, int height, const char* title) {
        if (!glfwInit()) {
            std::cerr << "GLFW initialization failed!" << std::endl;
            return;
        }

        // Set OpenGL version to 4.1 Core Profile (max on macOS)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        // Load OpenGL functions using GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // Set OpenGL viewport
        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glEnable(GL_DEPTH_TEST);
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::SwapBuffers() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Callback to resize viewport when window is resized
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }
}