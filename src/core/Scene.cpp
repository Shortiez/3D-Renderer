//
// Created by Ben Gotts on 25/01/2025.
//
#include <vector>
#include "Scene.h"

#include <imgui.h>

#include "../graphics/Renderer.h"
#include "../graphics/MeshLibrary.h"
#include "../lighting/Light.h"
#include "../lighting/DirectionalLight.h"
#include "../lighting/PointLight.h"
#include "../lighting/SpotLight.h"

using namespace std;

namespace BG3DRenderer::Core {

    Scene::Scene(Graphics::Renderer* renderer, Input* input) :
       renderer(renderer),
       input(input)
    {
        mainCamera = std::make_shared<Camera>(Camera(glm::vec3(0.0f, 0.0f, 3.0f)));
        renderer->SetCamera(mainCamera);

        Start();
    }

    Scene::~Scene() {

    }

    void Scene::AddSceneObject(SceneObject& sceneObject) {
        sceneObjects->push_back(sceneObject);
    }

    void Scene::RemoveSceneObject(SceneObject* sceneObject) {
        // TODO: Implement
    }

    void Scene::AddLight(std::unique_ptr<Lighting::Light> light) {
        sceneLights.push_back(std::move(light));
    }

    void Scene::RemoveLight(Lighting::Light* light){
    }

    void Scene::Start() {
        auto dirLight = std::make_unique<Lighting::DirectionalLight>();
        dirLight->transform.position = glm::vec3(1.2f, 1.0f, 2.0f);
        AddLight(std::move(dirLight));

        /*
        auto greenLight = std::make_unique<Lighting::PointLight>();
        greenLight->transform.position = glm::vec3(-2.0f, 1.0f, -2.0f);
        greenLight->diffuse = Colour::Green();
        greenLight->SetAttenuation(1.0f, 0.09f, 0.032f);
        AddLight(std::move(greenLight));

        auto blueLight = std::make_unique<Lighting::PointLight>();
        blueLight->transform.position = glm::vec3(-2.0f, 1.0f, -2.0f);
        blueLight->diffuse = Colour::Blue();
        blueLight->SetAttenuation(1.0f, 0.09f, 0.032f);
        AddLight(std::move(blueLight));
        */
        /*
        // Create a spotlight (like a flashlight)
        auto spotLight = std::make_unique<Lighting::SpotLight>();
        spotLight->transform.position = glm::vec3(0.0f, 3.0f, 0.0f);
        spotLight->SetDirection(glm::normalize(glm::vec3(0.0f, -1.0f, -1.0f)));
        spotLight->SetCutOffAngles(12.5f, 17.5f);
        spotLight->diffuse = Colour::Red();
        spotLight->SetAttenuation(1.0f, 0.09f, 0.032f);
        AddLight(std::move(spotLight));
*/
        
        auto material = make_shared<Graphics::Material>(Material::emerald);

        auto cube = MeshLibrary::Cube(1);
        cube.SetMaterial(material);
        SceneObject sceneObject = SceneObject(make_shared<Mesh>(cube));
        AddSceneObject(sceneObject);

        auto sphere = MeshLibrary::Sphere(0.5f, 24);
        sphere.SetMaterial(material);
        SceneObject sceneObject2 = SceneObject(make_shared<Mesh>(sphere));
        sceneObject2.transform.position = glm::vec3(3.0f, 0.0f, 0.0f);
        AddSceneObject(sceneObject2);
    }

    void Scene::Update(float deltaTime) {
        internalUpdate();

        // Add runtime logic here
        if(input->IsKeyHeld(GLFW_KEY_W))
            mainCamera->ProcessKeyboard(FORWARD, deltaTime);
        if(input->IsKeyHeld(GLFW_KEY_A))
            mainCamera->ProcessKeyboard(LEFT, deltaTime);
        if(input->IsKeyHeld(GLFW_KEY_S))
            mainCamera->ProcessKeyboard(BACKWARD, deltaTime);
        if(input->IsKeyHeld(GLFW_KEY_D))
            mainCamera->ProcessKeyboard(RIGHT, deltaTime);

        if (input->IsKeyPressed(GLFW_KEY_0))
        {
            GetSceneObject(0).mesh->GetMaterial()->SetColour(Colour::Red());
        }

        if (input->IsKeyHeld(GLFW_KEY_1))
        {
            GetSceneObject(0).mesh->GetMaterial()->SetColour(Colour::Green());
        }

        if (input->IsKeyPressed(GLFW_KEY_2))
        {
            GetSceneObject(0).mesh->GetMaterial()->SetColour(Colour::Blue());
        }

        //GetSceneObject(0).transform.Rotate(glm::vec3(0, 0, 1));
    }

    void Scene::internalUpdate() {
        renderer->UpdateFrameTime();

        // Update scene objects if needed
        for (auto& object : *sceneObjects) {
            object.Update();
        }

        for (auto& light : sceneLights) {
            light->Update();  // This will call the appropriate derived class Update()
        }
    }

    std::shared_ptr<vector<SceneObject>> Scene::GetSceneObjects() {
        return sceneObjects;
    }

    SceneObject& Scene::GetSceneObject(int index) const {
        if (sceneObjects->size() <= index) {
            throw std::out_of_range("Index out of range");
        }

        return sceneObjects->at(index);
    }

    std::vector<std::unique_ptr<Lighting::Light>>& Scene::GetSceneLights() {
        return sceneLights;
    }

    std::unique_ptr<Lighting::Light>& Scene::GetSceneLight(int index) const {
        if (index >= sceneLights.size()) {
            throw std::out_of_range("Light index out of range");
        }
        return const_cast<std::unique_ptr<Lighting::Light>&>(sceneLights[index]);
    }
    
    shared_ptr<Camera> Scene::GetCamera() {
        return mainCamera;
    }

    bool firstMouse = true;
    float lastX;
    float lastY;

    // glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
    void Scene::mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn) {
        if (ImGui::GetIO().WantCaptureMouse) return; // ✅ Prevent camera movement when ImGui is active

        Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
        if (!scene || !scene->mainCamera) return;

        float xPos = static_cast<float>(xPosIn);
        float yPos = static_cast<float>(yPosIn);

        static bool firstMouse = true;
        static float lastX, lastY;

        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos; // Reversed since y-coordinates go from bottom to top

        lastX = xPos;
        lastY = yPos;

        scene->mainCamera->ProcessMouseMovement(xOffset, yOffset);
    }

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
    void Scene::scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
        if (ImGui::GetIO().WantCaptureMouse) return; // ✅ Prevent scrolling if ImGui is using the scroll wheel

        Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
        if (!scene || !scene->mainCamera) return;

        scene->mainCamera->ProcessMouseScroll(static_cast<float>(yOffset));
    }
}
