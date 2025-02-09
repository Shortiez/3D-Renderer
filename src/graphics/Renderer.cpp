//
// Created by Ben Gotts on 25/01/2025.
//

#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <utility>
#include "ShaderManager.h"
#include "../core/Scene.h"  // Include full definition of Scene
#include "../lighting/Light.h"

namespace BG3DRenderer::Graphics{

    Renderer::Renderer(){
        activeShader = ShaderManager::loadShader("src/shaders/VertexShader.glsl", "src/shaders/FragmentShader.glsl");

        activeShader->Use();
    }

    void Renderer::Render(Scene& scene) {
        activeShader->Use();

        // Update view and projection matrices
        glm::mat4 view = activeCamera->GetViewMatrix();

        // TODO: FIX THIS ASPECT RATIO
        glm::mat4 projection = glm::perspective(
                glm::radians(activeCamera->Zoom),
#ifdef __APPLE__
                16.0f / 10.0f,
#else  // Assume Windows
                16.0f / 9.0f,
#endif
                0.1f,
                100.0f
        );

        activeShader->SetMat4("view", view);
        activeShader->SetMat4("projection", projection);

        for (auto& object : *scene.GetSceneObjects()) {
            object.Render(activeShader);
        }

        for (auto& light : scene.GetSceneLights()) {
            light->Render(activeShader, activeCamera);
        }
    }

    void Renderer::SetCamera(std::shared_ptr<Camera> camera) {
        activeCamera = camera;
    }

    std::shared_ptr<Shader> Renderer::GetShader() {
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
