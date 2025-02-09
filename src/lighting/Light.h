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
        virtual ~Light() = default;

        Colour ambient = Colour(0.2f, 0.2f, 0.2f);
        Colour diffuse = Colour(0.5f, 0.5f, 0.5f);
        Colour specular = Colour(1.0f, 1.0f, 1.0f);

        float intensity = 1.0f;

        virtual void Update();
        virtual void Render(std::shared_ptr<Graphics::Shader> shader, std::shared_ptr<Core::Camera> camera);

        Core::Transform transform;
        std::shared_ptr<Graphics::Mesh> mesh;
    };
}

#endif //LIGHT_H
