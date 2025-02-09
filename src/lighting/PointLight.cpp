#include "PointLight.h"

namespace BG3DRenderer::Lighting {
    PointLight::PointLight() : Light() {
        // Default attenuation values
        constant = 1.0f;
        linear = 0.09f;
        quadratic = 0.032f;
    }

    void PointLight::SetAttenuation(float constant, float linear, float quadratic) {
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
    }

    void PointLight::Update() {
        // Add any point light specific update logic here
        Light::Update();
    }

    void PointLight::Render(std::shared_ptr<Graphics::Shader> shader, std::shared_ptr<Core::Camera> camera) {
        Light::Render(shader, camera);

        shader->SetVec3("pointLight.ambient", this->ambient.ToVec3());
        shader->SetVec3("pointLight.diffuse", this->diffuse.ToVec3());
        shader->SetVec3("pointLight.specular", this->specular.ToVec3());
        shader->SetVec3("pointLight.position", this->transform.position);
        shader->SetFloat("pointLight.constant", this->constant);
        shader->SetFloat("pointLight.linear", this->linear);
        shader->SetFloat("pointLight.quadratic", this->quadratic);

        shader->SetBool("usePointLights", true);

        std::cout << "Point Light" << std::endl;
    }
}