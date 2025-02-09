//
// Created by Ben Gotts on 25/01/2025.
//
#include <vector>
#include "Scene.h"

#include <imgui.h>

#include "../graphics/Renderer.h"
#include "../graphics/MeshLibrary.h"
#include "../lighting/Light.h"

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

    void Scene::AddLight(Lighting::Light& light) {
        sceneLights->push_back(light);
    }

    void Scene::RemoveLight(Lighting::Light* light){

    }

    void Scene::Start() {
        Lighting::Light light = Lighting::Light();
        light.transform.position = glm::vec3(1.2f, 1.0f, 2.0f);
        AddLight(light);

        auto mesh = MeshLibrary::Cube(1.0f);

        auto material = std::make_shared<Material>();
        material->SetBaseColor(Colour::Red());

        mesh.SetMaterial(material);

        SceneObject sceneObject = SceneObject(make_shared<Mesh>(mesh));
        AddSceneObject(sceneObject);
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
            GetSceneObject(0).mesh->GetMaterial()->SetBaseColor(Colour::Red());
        }

        if (input->IsKeyHeld(GLFW_KEY_1))
        {
            GetSceneObject(0).mesh->GetMaterial()->SetBaseColor(Colour::Green());
        }

        if (input->IsKeyPressed(GLFW_KEY_2))
        {
            GetSceneObject(0).mesh->GetMaterial()->SetBaseColor(Colour::Blue());
        }

        GetSceneObject(0).transform.Rotate(glm::vec3(0, 0, 1));
    }

    void Scene::internalUpdate() {
        renderer->UpdateFrameTime();

        // Update scene objects if needed
        for (auto& object : *sceneObjects) {
            object.Update();
        }

        for (auto& light : *sceneLights) {
            light.Update();
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

    std::shared_ptr<vector<Lighting::Light>> Scene::GetSceneLights() {
        return sceneLights;
    }

    Lighting::Light& Scene::GetSceneLight(int index) const {
        return sceneLights->at(index);
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
