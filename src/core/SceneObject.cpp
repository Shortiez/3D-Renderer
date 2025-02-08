#include "SceneObject.h"
#include <glm/ext/matrix_transform.hpp>
#include <utility>

namespace BG3DRenderer::Core {

    SceneObject::SceneObject(std::shared_ptr<Mesh> mesh) : mesh(std::move(mesh)) {
    }

    SceneObject::~SceneObject() = default;

    void SceneObject::Update() {
        // Optional update logic (e.g., animations or other updates)
    }

    void SceneObject::Render(std::shared_ptr<Shader> shader) {
        shader->SetMat4("model", transform);
        mesh->DrawMesh(shader);
    }

    void SceneObject::Translate(glm::vec3 position) {
        transform = glm::translate(transform, position);
    }

    void SceneObject::Rotate(float angle, glm::vec3 axis) {
        transform = glm::rotate(transform, angle, axis);
    }

    void SceneObject::Scale(glm::vec3 scale) {
        transform = glm::scale(transform, scale);
    }
}