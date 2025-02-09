#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../graphics/Mesh.h"
#include "../graphics/Shader.h"
#include <memory>

#include "Transform.h"

using namespace BG3DRenderer::Graphics;

namespace BG3DRenderer::Core {
    class SceneObject {
    public:
        SceneObject(std::shared_ptr<Mesh> mesh);
        ~SceneObject();

        virtual void Update();
        virtual void Render(std::shared_ptr<Shader> shader);

        Transform transform;
        std::shared_ptr<Mesh> mesh;
    };
}

#endif //SCENEOBJECT_H
