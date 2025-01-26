//
// Created by Ben Gotts on 25/01/2025.
//

#include "Renderer.h"

#include <GLFW/glfw3.h>

#include <utility>

namespace BG3DRenderer::Graphics{

    Renderer::Renderer(std::shared_ptr<ShaderUtility> shader): activeShader(std::move(shader)) {
    }

    void Renderer::Render(const std::vector<SceneObject*>& objects) {
        activeShader->Use();

        // Update view and projection matrices
        glm::mat4 view = activeCamera->GetViewMatrix();
        glm::mat4 projection = glm::perspective(
            glm::radians(activeCamera->Zoom),
            16.0f / 9.0f,
            0.1f,
            100.0f
        );

        activeShader->SetMat4("view", view);
        activeShader->SetMat4("projection", projection);

        for (auto& object : objects) {
            object->Render(activeShader);
        }
    }

    void Renderer::SetCamera(const std::shared_ptr<Camera> camera) {
        activeCamera = camera;
    }

    std::shared_ptr<ShaderUtility>Renderer::GetShader() const {
        return activeShader;
    }

    void Renderer::UpdateFrameTime() {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Update FPS buffer
        fpsBuffer[fpsBufferIndex] = deltaTime > 0 ? 1.0f / deltaTime : 0;
        fpsBufferIndex = (fpsBufferIndex + 1) % FPS_BUFFER_SIZE;

        minFrameTime = std::min(minFrameTime, deltaTime);
        maxFrameTime = std::max(maxFrameTime, deltaTime);

        frameTimeHistory.push_back(deltaTime);
        if (frameTimeHistory.size() > 120)
            frameTimeHistory.erase(frameTimeHistory.begin());
    }

}
