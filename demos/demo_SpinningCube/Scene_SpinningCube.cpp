//
// Created by gotts on 10/02/2025.
//

#include "Scene_SpinningCube.h"

#include <utility>

#include "../../src/graphics/MeshLibrary.h"
#include "../../src/lighting/DirectionalLight.h"
#include "../../src/lighting/PointLight.h"
#include "../../src/lighting/SpotLight.h"

namespace BG3DRenderer::Demos{

    // Constructor: call the base Scene constructor with renderer and input.
    Scene_SpinningCube::Scene_SpinningCube(Renderer* renderer, Core::Camera* cam, Core::Input* input)
        : Core::Scene(renderer, cam, input)
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

        auto spotLight = std::make_unique<Lighting::SpotLight>();
        spotLight->transform.Translate(glm::vec3(0, 0, 5));
        spotLight->SetDirection(glm::vec3(0, 0, -1));
        spotLight->diffuse = Colour::Yellow();
        AddLight(std::move(spotLight));

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
