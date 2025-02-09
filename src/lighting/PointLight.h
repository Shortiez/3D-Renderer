#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

namespace BG3DRenderer::Lighting {
    class PointLight : public Light {
    public:
        PointLight();
        ~PointLight() override = default;

        // Attenuation factors
        float constant;
        float linear;
        float quadratic;

        // Setters for properties
        void SetAttenuation(float constant, float linear, float quadratic);
        
        void Update() override;
        void Render(std::shared_ptr<Graphics::Shader> shader, std::shared_ptr<Core::Camera> camera, int lightIndex) override;
    };
}

#endif //POINTLIGHT_H