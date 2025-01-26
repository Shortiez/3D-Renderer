//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef SCENE_H
#define SCENE_H

#include "SceneObject.h"
#include <memory>

#include "Camera.h"
#include "../graphics/Renderer.h"
#include "Input.h"

using namespace std;

namespace BG3DRenderer::Core {
    class Scene {
    private:
        shared_ptr<vector<SceneObject>> sceneObjects = make_shared<vector<SceneObject>>();
        Renderer& renderer;
        shared_ptr<Camera> mainCamera;
        Input& input;

        void internalUpdate();
    public:
        Scene(Renderer& renderer, Input& input);
        ~Scene();
        void AddSceneObject(SceneObject& sceneObject);
        void RemoveSceneObject(SceneObject* sceneObject);

        void Start();
        void Update(float deltaTime);
        void Render();

        SceneObject& GetSceneObject(int index);
        int GetSceneObjectCount() {
            return sceneObjects->size();
        }

        shared_ptr<Camera> GetCamera();

        static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
        static void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn);
    };
}

#endif //SCENE_H
