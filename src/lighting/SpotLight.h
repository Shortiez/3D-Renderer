#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"

namespace BG3DRenderer::Lighting {
    class SpotLight : public Light {
    public:
        SpotLight();
        ~SpotLight() override = default;

        // Spotlight properties
        float cutOff;        // Inner cone angle (in degrees)
        float outerCutOff;   // Outer cone angle (in degrees)
        
        // Attenuation factors
        float constant;
        float linear;
        float quadratic;

        // Setters for properties
        void SetCutOffAngles(float innerAngle, float outerAngle);
        void SetAttenuation(float constant, float linear, float quadratic);
        void SetDirection(const glm::vec3& direction);
        
        void Update() override;
        void Render(std::shared_ptr<Graphics::Shader> shader, std::shared_ptr<Core::Camera> camera) override;
    private:
        glm::vec3 direction;
    };
}

#endif //SPOTLIGHT_H