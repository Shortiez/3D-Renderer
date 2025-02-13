//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef SCENE_H
#define SCENE_H

#include "SceneObject.h"
#include <memory>
#include "Camera.h"
#include "Input.h"
#include "../lighting/Light.h"

namespace BG3DRenderer::Lighting
{
    class Light;
}

using namespace std;

// Forward declaration
namespace BG3DRenderer::Graphics {
    class Renderer;
}

namespace BG3DRenderer::Core {
    class Scene {
    private:
        shared_ptr<vector<SceneObject>> sceneObjects = make_shared<vector<SceneObject>>();
        std::vector<std::unique_ptr<Lighting::Light>> sceneLights;
        Camera* mainCamera;

        Renderer* renderer;
        Input* input;

        void internalUpdate();
    public:
        Scene(Renderer* renderer, Camera* cam, Input* input);
        virtual ~Scene();

        void AddSceneObject(SceneObject& sceneObject);
        void RemoveSceneObject(SceneObject* sceneObject);

        void AddLight(std::unique_ptr<Lighting::Light> light);
        void RemoveLight(Lighting::Light* light);

        virtual void Start();
        void Stop();
        virtual void Update(float deltaTime);

        std::shared_ptr<vector<SceneObject>> GetSceneObjects();
        SceneObject& GetSceneObject(int index) const;
        int GetSceneObjectCount()
        {
            return sceneObjects->size();
        }

        vector<unique_ptr<Lighting::Light>>& GetSceneLights();
        unique_ptr<Lighting::Light>& GetSceneLight(int index) const;
        int GetSceneLightsCount()
        {
            return sceneLights.size();
        }

        Camera* GetCamera(){
            return mainCamera;
        }

        static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
        static void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn);
    };
}

#endif //SCENE_H
