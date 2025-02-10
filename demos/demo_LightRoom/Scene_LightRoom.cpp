//
// Created by gotts on 10/02/2025.
//

#include "Scene_LightRoom.h"

#include "../../src/graphics/MeshLibrary.h"
#include "../../src/lighting/DirectionalLight.h"

namespace BG3DRenderer::Demos::LightRoom{

    // Constructor: call the base Scene constructor with renderer and input.
    Scene_LightRoom::Scene_LightRoom(Renderer* renderer, Core::Input* input)
        : Core::Scene(renderer, input)
    {
        // Add any scene-specific initialization here.
    }

    // Destructor: add any scene-specific cleanup here if needed.
    Scene_LightRoom::~Scene_LightRoom() {
        // Cleanup resources if necessary.
    }

    void Scene_LightRoom::Start(){
        Scene::Start();

        auto dirLight = make_unique<Lighting::DirectionalLight>();
        AddLight(std::move(dirLight));

        auto boxMat = std::make_shared<Material>(Material::whitePlastic);
        auto boxMesh = std::make_shared<Mesh>(MeshLibrary::Cube(5));
        boxMesh->SetMaterial(boxMat);

        Core::SceneObject boxSceneObject = Core::SceneObject(boxMesh);
        AddSceneObject(boxSceneObject);
    }

    void Scene_LightRoom::Update(float deltaTime){
        Scene::Update(deltaTime);
    }
}
