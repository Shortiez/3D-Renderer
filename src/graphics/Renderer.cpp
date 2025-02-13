//
// Created by Ben Gotts on 25/01/2025.
//

#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <utility>
#include "ShaderManager.h"
#include "../core/Scene.h"  // Include full definition of Scene
#include "../core/SceneManager.h"
#include "../lighting/Light.h"

namespace BG3DRenderer::Graphics
{
    Renderer::Renderer(){
        activeShader = ShaderManager::loadShader("src/shaders/VertexShader.glsl", "src/shaders/FragmentShader.glsl");

        activeShader->Use();
    }

    Renderer::~Renderer(){
        delete activeCamera;
    }

    void Renderer::Render() {
        assert(activeCamera != nullptr);

        activeShader->Use();

        // Update view and projection matrices
        glm::mat4 view = activeCamera->GetViewMatrix();

        // TODO: FIX THIS TO USE A STATIC ASPECT RATIO METHOD
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

        activeShader->SetInt("activePointLights", std::count_if(SceneManager::GetInstance().GetCurrentScene()->GetSceneLights().begin(),
                                                                SceneManager::GetInstance().GetCurrentScene()->GetSceneLights().end(), [](const auto& light)
                                                                {
                                                                    return light->GetType() == LightType::Point;
                                                                }));

        for (auto& object : *SceneManager::GetInstance().GetCurrentScene()->GetSceneObjects()) {
            object.Render(activeShader);
        }

        for (int i = 0; i < SceneManager::GetInstance().GetCurrentScene()->GetSceneLights().size(); ++i)
        {
            auto& light = SceneManager::GetInstance().GetCurrentScene()->GetSceneLights()[i];
            if (light->GetType() == LightType::Point)
            {
                light->Render(activeShader, activeCamera, i - 1);
            }
            else
            {
                light->Render(activeShader, activeCamera);
            }
        }
    }

    void Renderer::SetCamera(Camera* camera) {
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
