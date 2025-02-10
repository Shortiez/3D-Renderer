#include "SceneManager.h"

namespace BG3DRenderer::Core {

SceneManager& SceneManager::GetInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::LoadScene(std::unique_ptr<Scene> newScene) {
    // Optionally, perform cleanup for the existing scene here
    currentScene = std::move(newScene);
    if (currentScene) {
        currentScene->Start();
    }
}

Scene* SceneManager::GetCurrentScene() const {
    return currentScene.get();
}

void SceneManager::UpdateCurrentScene(float deltaTime) {
    if (currentScene) {
        currentScene->Update(deltaTime);
    }
}

} // namespace BG3DRenderer::Core