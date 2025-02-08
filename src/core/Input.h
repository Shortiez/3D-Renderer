//
// Created by Ben Gotts on 23/01/2025.
//

#ifndef LEARNINGOPENGL_INPUT_H
#define LEARNINGOPENGL_INPUT_H

#include <unordered_map>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace BG3DRenderer::Core {
    class Input {
    public:
        Input(GLFWwindow* targetWindow);

        // Keyboard input
        bool IsKeyPressed(int key);
        bool IsKeyHeld(int key);
        bool IsKeyReleased(int key);

        bool IsMouseButtonPressed(int button);

        // Mouse input
        glm::vec2 GetMousePosition();
        glm::vec2 GetMouseOffset();
    private:
        GLFWwindow* window;

        bool firstMouse = true;
        float mouseX = 0.0f;
        float mouseY = 0.0f;
        std::unordered_map<int, bool> keyState;
    };
}

#endif //LEARNINGOPENGL_INPUT_H
