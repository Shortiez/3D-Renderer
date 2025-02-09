#include "DirectionalLight.h"
#include "../core/Application.h"

namespace BG3DRenderer::Lighting {
    using namespace Core;
    DirectionalLight::DirectionalLight() : Light() {
        // Initialize any DirectionalLight-specific members
        direction = glm::vec3(-0.2f, -1.0f, -0.3f); // Default direction

        type = LightType::Directional;
    }

    void DirectionalLight::Update() {
        // You might want to implement specific update logic for directional light
        // Or just leave it empty if the light direction is static
        Light::Update();
    }

    void DirectionalLight::Render(std::shared_ptr<Graphics::Shader> shader, std::shared_ptr<Core::Camera> camera) {
        // Call base class Render to handle common light properties
        Light::Render(shader, camera);

        // Add directional light specific uniforms
        shader->SetVec3("dirLight.direction", direction);
        shader->SetVec3("dirLight.ambient", ambient.ToVec3());
        shader->SetVec3("dirLight.diffuse", diffuse.ToVec3());
        shader->SetVec3("dirLight.specular", specular.ToVec3());

        // Enable directional light in the shader
        shader->SetBool("useDirLight", true);

        std::cout << "Direction Light" << std::endl;
    }
}