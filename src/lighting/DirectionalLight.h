//
// Created by Ben Gotts on 09/02/2025.
//

#ifndef INC_3D_RENDERER_DIRECTIONALLIGHT_H
#define INC_3D_RENDERER_DIRECTIONALLIGHT_H

#include <iostream>
#include "../core/Camera.h"
#include "../core/SceneObject.h"
#include "Light.h"

namespace BG3DRenderer::Lighting{
    class DirectionalLight : public Light {
    public:
        DirectionalLight();

        // Override the base class virtual functions
        void Update() override;
        void Render(std::shared_ptr<Graphics::Shader> shader, std::shared_ptr<Core::Camera> camera) override;

        // DirectionalLight specific members...
        glm::vec3 direction;
    };
}

#endif //INC_3D_RENDERER_DIRECTIONALLIGHT_H
