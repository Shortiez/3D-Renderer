//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShaderUtility.h"

namespace BG3DRenderer::Graphics{
    class Material {
    private:
        glm::vec4 BaseColor;
    public:
        Material();

        void SetBaseColor(const glm::vec4 color);
        void UpdateMaterial(ShaderUtility* shader);
    };
}

#endif //MATERIAL_H
