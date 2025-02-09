#include "SceneObject.h"
#include <glm/ext/matrix_transform.hpp>
#include <utility>

namespace BG3DRenderer::Core {

    SceneObject::SceneObject(std::shared_ptr<Mesh> mesh) {
        this->mesh = mesh;
    }

    SceneObject::~SceneObject() = default;

    void SceneObject::Update() {
        // Optional update logic (e.g., animations or other updates)
    }

    void SceneObject::Render(std::shared_ptr<Shader> shader) {
        shader->SetMat4("model", transform.GetModelMatrix());
        mesh->DrawMesh(shader);
    }
}