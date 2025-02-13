#include "SceneManager.h"

#include "Application.h"

namespace BG3DRenderer::Core{
    SceneManager& SceneManager::GetInstance() {
        static SceneManager instance;
        return instance;
    }

    void SceneManager::LoadScene(std::unique_ptr<Scene> newScene) {
        if (currentScene) {
            currentScene->Stop();
        }

        // Optionally, perform cleanup for the existing scene here
        currentScene = std::move(newScene);

        currentScene->Start();

        // Notify all registered observers that the scene has changed
        for (auto& callback : sceneChangeCallbacks) {
            if (callback) {
                callback(currentScene.get());
            }
        }
    }

    Scene* SceneManager::GetCurrentScene() const {
        return currentScene.get();
    }

    void SceneManager::RegisterSceneChangeCallback(const SceneChangeCallback& callback) {
        sceneChangeCallbacks.push_back(callback);
    }
} // namespace BG3DRenderer::Core