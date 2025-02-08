//
// Created by Ben Gotts on 25/01/2025.
//
#include <vector>
#include "Scene.h"
#include "../graphics/Renderer.h"
#include "../graphics/MeshLibrary.h"

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

    void Scene::Start() {
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

        GetSceneObject(0).Rotate(deltaTime, glm::vec3(0, 0, 1));
    }

    void Scene::internalUpdate() {
        renderer->UpdateFrameTime();

        // Update scene objects if needed
        for (auto& object : *sceneObjects) {
            object.Update();
        }
    }

    void Scene::Render() {
        // Collect raw pointers for rendering
        std::vector<SceneObject*> objectsToRender;
        for (auto& object : *sceneObjects) {
            objectsToRender.push_back(&object);
        }

        renderer->Render(objectsToRender);
    }

    SceneObject& Scene::GetSceneObject(int index) {
        return sceneObjects->at(index);
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
        Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
        if (!scene || !scene->mainCamera) return;

        float xPos = static_cast<float>(xPosIn);
        float yPos = static_cast<float>(yPosIn);

        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos; // reversed since y-coordinates go from bottom to top

        lastX = xPos;
        lastY = yPos;

        scene->mainCamera->ProcessMouseMovement(xOffset, yOffset);
    }


    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
    void Scene::scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
        Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
        if (!scene || !scene->mainCamera) return;

        scene->mainCamera->ProcessMouseScroll(static_cast<float>(yOffset));
    }
}
