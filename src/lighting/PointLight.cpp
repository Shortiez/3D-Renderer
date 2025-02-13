#include "PointLight.h"
#include <sstream>

namespace BG3DRenderer::Lighting {
    PointLight::PointLight() : Light() {
        // Default attenuation values
        constant = 1.0f;
        linear = 0.09f;
        quadratic = 0.032f;

        type = LightType::Point;
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

    void PointLight::Render(std::shared_ptr<Graphics::Shader> shader,
                            Core::Camera* camera,
                            int lightIndex) {
        // Call the base class render to update any common uniforms.
        Light::Render(shader, camera);

        // Use a string stream to construct the uniform name with the correct array index
        std::stringstream ss;

        ss << "pointLights[" << lightIndex << "].ambient";
        shader->SetVec3(ss.str(), this->ambient.ToVec3());
        ss.str(""); // clear the stringstream

        ss << "pointLights[" << lightIndex << "].diffuse";
        shader->SetVec3(ss.str(), this->diffuse.ToVec3());
        ss.str("");

        ss << "pointLights[" << lightIndex << "].specular";
        shader->SetVec3(ss.str(), this->specular.ToVec3());
        ss.str("");

        ss << "pointLights[" << lightIndex << "].position";
        shader->SetVec3(ss.str(), this->transform.position);
        ss.str("");

        ss << "pointLights[" << lightIndex << "].constant";
        shader->SetFloat(ss.str(), this->constant);
        ss.str("");

        ss << "pointLights[" << lightIndex << "].linear";
        shader->SetFloat(ss.str(), this->linear);
        ss.str("");

        ss << "pointLights[" << lightIndex << "].quadratic";
        shader->SetFloat(ss.str(), this->quadratic);
        ss.str("");

        // Make sure the boolean flag for point lights is set in the shader.
        shader->SetBool("usePointLights", true);

        std::cout << "Point Light Index: " << lightIndex << std::endl;
    }
}