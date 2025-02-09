//
// Created by gotts on 08/02/2025.
//

#include "Light.h"

#include "../core/Application.h"
#include "../graphics/MeshLibrary.h"

namespace BG3DRenderer::Lighting{

    Light::Light(){
        mesh = std::make_shared<Mesh>(MeshLibrary::Sphere(0.1f, 12));
    }

    void Light::Update() {
        static float angle = 0.0f;
        float radius = 2.0f; // Radius of the orbit
        float speed = glm::pi<float>() / 4.0f; // Speed of the orbit (radians per second)

        angle += speed * Application::DeltaTime; // Update the angle based on the frame time

        // Calculate the new position
        transform.position.x = radius * cos(angle);
        transform.position.z = radius * sin(angle);
    }

    void Light::Render(std::shared_ptr<Shader> shader, std::shared_ptr<Core::Camera> camera) {
        shader->SetVec3("lightPos", transform.position);
        shader->SetVec3("viewPos", camera->Position);

        shader->SetVec3("light.ambient", ambient.ToVec3());
        shader->SetVec3("light.diffuse", diffuse.ToVec3());
        shader->SetVec3("light.specular", specular.ToVec3());

        shader->SetMat4("model", transform.GetModelMatrix());
        mesh->DrawMesh(shader);
    }
}
