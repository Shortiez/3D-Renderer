//
// Created by gotts on 10/02/2025.
//

#include "Scene_SpinningCube.h"

#include "../../src/graphics/MeshLibrary.h"
#include "../../src/lighting/DirectionalLight.h"

namespace BG3DRenderer::Demos::SpinningCube{

    // Constructor: call the base Scene constructor with renderer and input.
    Scene_SpinningCube::Scene_SpinningCube(Renderer* renderer, Core::Input* input)
        : Core::Scene(renderer, input)
    {
        // Add any scene-specific initialization here.
    }

    // Destructor: add any scene-specific cleanup here if needed.
    Scene_SpinningCube::~Scene_SpinningCube() {
        // Cleanup resources if necessary.
    }

    void Scene_SpinningCube::Start(){
        Scene::Start();

        auto light = std::make_unique<Lighting::DirectionalLight>();
        AddLight(std::move(light));

        auto material = std::make_shared<Material>(Material::pearl);

        auto cube = std::make_shared<Mesh>(MeshLibrary::Cube(1));
        cube->SetMaterial(material);

        Core::SceneObject sceneObject = Core::SceneObject(cube);
        AddSceneObject(sceneObject);
    }

    void Scene_SpinningCube::Update(float deltaTime){
        Scene::Update(deltaTime);

        GetSceneObject(0).transform.Rotate(glm::vec3(0, 0, 1));
    }
}
