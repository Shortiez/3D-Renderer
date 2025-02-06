#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../graphics/Mesh.h"
#include "../graphics/Shader.h"
#include <memory>

using namespace BG3DRenderer::Graphics;

namespace BG3DRenderer::Core {
    class SceneObject {
    public:
        SceneObject(Mesh& mesh, Material& mat);
        ~SceneObject();

        void Update();
        void Render(std::shared_ptr<Shader> shader);

        void Translate(glm::vec3 position);
        void Rotate(float angle, glm::vec3 axis);
        void Scale(glm::vec3 scale);

        Mesh mesh;
        Material material;
        glm::mat4 transform = glm::mat4(1.0f);
    };
}

#endif //SCENEOBJECT_H
