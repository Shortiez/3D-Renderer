//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "Shader.h"

namespace BG3DRenderer::Graphics{
    class Material {
    private:
        glm::vec4 BaseColor;
    public:
        Material();

        void SetBaseColor(glm::vec4 color);
        void UpdateMaterial(std::shared_ptr<Shader> shader);
    };
}

#endif //MATERIAL_H
