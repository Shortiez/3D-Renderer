#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include "Scene.h"  // Base scene header

namespace BG3DRenderer::Core {

class SceneManager {
public:
    // Singleton access (you could also use dependency injection)
    static SceneManager& GetInstance();

    // Loads and switches to a new scene instance
    void LoadScene(std::unique_ptr<Scene> newScene);

    // Gets a pointer to the current scene
    Scene* GetCurrentScene() const;

    // Updates the current scene
    void UpdateCurrentScene(float deltaTime);

private:
    // Private constructor for singleton usage
    SceneManager() = default;
    ~SceneManager() = default;

    // Delete copy constructor and assignment operator
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    // The current active scene
    std::unique_ptr<Scene> currentScene;
};

} // namespace BG3DRenderer::Core

#endif // SCENE_MANAGER_H