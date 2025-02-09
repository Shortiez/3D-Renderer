//
// Created by gotts on 08/02/2025.
//

#include "Transform.h"

namespace BG3DRenderer::Core {
    Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
        position(position),
        rotation(rotation),
        scale(scale)
    {
    }

    glm::mat4 Transform::GetModelMatrix() {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, position);

        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::scale(model, scale);

        return model;
    }

    void Transform::Translate(glm::vec3 position) {
        this->position += position;
    }

    void Transform::Rotate(glm::vec3 rotation) {
        // Add wrapping so rotation is locked between 0 and 360
        if (this->rotation.x + rotation.x > 360) {
            this->rotation.x = 0;
        } else if (this->rotation.x + rotation.x < 0) {
            this->rotation.x = 360;
        }

        this->rotation += rotation;
    }

    void Transform::Scale(glm::vec3 scale) {
        this->scale += scale;
    }
}