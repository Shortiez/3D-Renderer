//
// Created by Ben Gotts on 23/01/2025.
//

#include "Input.h"
#include "glm/vec2.hpp"

namespace BG3DRenderer::Core {
    Input::Input(GLFWwindow *targetWindow) : window(targetWindow) {
        // Get initial mouse Position
        double mousePosX, mousePosY;
        glfwGetCursorPos(targetWindow, &mousePosX, &mousePosY);

        mouseX = static_cast<float>(mousePosX);
        mouseY = static_cast<float>(mousePosY);
    }

    bool Input::IsKeyPressed(int key) {
        bool isPressed = glfwGetKey(window, key) == GLFW_PRESS;
        if (isPressed && !keyState[key]) {
            keyState[key] = true;
            return true;
        }
        keyState[key] = isPressed;
        return false;
    }

    bool Input::IsKeyHeld(int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool Input::IsKeyReleased(int key) {
        bool isReleased = glfwGetKey(window, key) == GLFW_RELEASE;
        if (isReleased && keyState[key]) {
            keyState[key] = false;
            return true;
        }
        keyState[key] = !isReleased;
        return false;
    }

    bool Input::IsMouseButtonPressed(int button) {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition() {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return glm::vec2(static_cast<float>(xPos), static_cast<float>(yPos));
    }

    glm::vec2 Input::GetMouseOffset() {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        float xOffset = static_cast<float>(xPos) - mouseX;
        float yOffset = mouseY - static_cast<float>(yPos);  // Reversed for OpenGL coordinate system

        mouseX = static_cast<float>(xPos);
        mouseY = static_cast<float>(yPos);

        return glm::vec2(xOffset, yOffset);
    }
}