//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "Shader.h"

struct Colour;
namespace BG3DRenderer::Graphics{
    class Material {
    private:
        Colour BaseColor;
    public:
        Material();

        void SetBaseColor(Colour color);
        void UpdateMaterial(std::shared_ptr<Shader> shader);

        static std::shared_ptr<Material> GetDefaultMaterial();
    };
}

#endif //MATERIAL_H
