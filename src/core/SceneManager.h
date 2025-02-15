#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include "Scene.h"  // Base scene header

namespace BG3DRenderer::Core{
    class SceneManager {
    private:
        // Private constructor for singleton usage
        SceneManager() = default;
        ~SceneManager() = default;

        // Delete copy constructor and assignment operator
        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(const SceneManager&) = delete;

        // The current active scene
        std::unique_ptr<Scene> currentScene;

        using SceneChangeCallback = std::function<void(Scene*)>;
        // Store the registered callbacks
        std::vector<SceneChangeCallback> sceneChangeCallbacks;

        shared_ptr<Renderer> renderer;
        shared_ptr<Input> input;
        shared_ptr<Camera> mainCamera;
    public:
        // Singleton access (you could also use dependency injection)
        static SceneManager& GetInstance();

        // Loads and switches to a new scene instance
        void LoadScene(std::unique_ptr<Scene> newScene);
        Scene* GetCurrentScene() const;

        void RegisterSceneChangeCallback(const SceneChangeCallback& callback);
    };
} // namespace BG3DRenderer::Core

#endif // SCENE_MANAGER_H