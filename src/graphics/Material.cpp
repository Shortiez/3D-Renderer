//
// Created by Ben Gotts on 25/01/2025.
//

#include "Material.h"

namespace BG3DRenderer::Graphics {

    Material::Material() {
        BaseColor = {0, 1, 0, 1};
    }

    void Material::UpdateMaterial(std::shared_ptr<Shader> shader) {
        if (!shader) {
            std::cerr << "Material::UpdateMaterial - Shader is null!" << std::endl;
            return;
        }

        shader->SetColour("BaseColour", BaseColor);

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error in Material::UpdateMaterial: " << err << std::endl;
        }
    }

    void Material::SetBaseColor(const Colour color) {
        BaseColor = color;
    }

    std::shared_ptr<Material> Material::GetDefaultMaterial() {
        return std::make_shared<Material>();;
    }
}