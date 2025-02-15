//
// Created by Ben Gotts on 25/01/2025.
//
#include <utility>
#include <vector>
#include "Scene.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>

#include "../graphics/Renderer.h"
#include "../graphics/MeshLibrary.h"
#include "../lighting/Light.h"
#include "../lighting/DirectionalLight.h"
#include "../lighting/PointLight.h"
#include "../lighting/SpotLight.h"

using namespace std;

namespace BG3DRenderer::Core {

    Scene::Scene(Graphics::Renderer* renderer, Camera* cam, Input* input) :
       mainCamera(cam),
       renderer(renderer),
       input(input){
    }

    Scene::~Scene() {
        delete renderer;
        delete input;
        delete mainCamera;
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
    }

    void Scene::Stop(){
        sceneObjects->clear();
        sceneLights.clear();
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

    bool firstMouse = true;
    float lastX;
    float lastY;

    // glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
    void Scene::mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn) {
        ImGui_ImplGlfw_CursorPosCallback(window, xPosIn, yPosIn);

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
        ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);

        if (ImGui::GetIO().WantCaptureMouse) return; // ✅ Prevent scrolling if ImGui is using the scroll wheel

        Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
        if (!scene || !scene->mainCamera) return;

        scene->mainCamera->ProcessMouseScroll(static_cast<float>(yOffset));
    }
}
