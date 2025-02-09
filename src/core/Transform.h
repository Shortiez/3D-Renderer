//
// Created by gotts on 08/02/2025.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#endif //TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace BG3DRenderer::Core {
    class Transform {
    public:
        Transform() = default;
        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        glm::mat4 GetModelMatrix();

        void Translate(glm::vec3 position);
        void Rotate(glm::vec3 rotation);
        void Scale(glm::vec3 scale);
    };
}