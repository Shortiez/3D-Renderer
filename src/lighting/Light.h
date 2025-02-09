//
// Created by gotts on 08/02/2025.
//

#ifndef LIGHT_H
#define LIGHT_H
#include "../core/Camera.h"
#include "../core/SceneObject.h"

namespace BG3DRenderer::Lighting{
    class Light{
    public:
        Light();

        float intensity = 1.0f;
        Colour colour = Colour::White();

        void Update();
        void Render(std::shared_ptr<Graphics::Shader> shader, std::shared_ptr<Core::Camera> camera);

        Core::Transform transform;
        std::shared_ptr<Graphics::Mesh> mesh;
    };
}

#endif //LIGHT_H
