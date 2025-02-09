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
        Colour ambient = Colour::White();
        Colour diffuse = Colour::White();
        Colour specular = Colour::White();
        float shininess = 32.0f;
    public:
        Material();
        Material(Colour ambient, Colour diffuse, Colour specular, float shininess);

        void SetColour(Colour colour);
        void SetAmbient(Colour ambient);
        void SetDiffuse(Colour diffuse);
        void SetSpecular(Colour specular);
        void SetShininess(float shininess);

        void UpdateMaterial(std::shared_ptr<Shader> shader);

        static std::shared_ptr<Material> GetDefaultMaterial();


        // Static Material definitions
        static Material emerald;
        static Material jade;
        static Material obsidian;
        static Material pearl;
        static Material ruby;
        static Material turquoise;
        static Material brass;
        static Material bronze;
        static Material chrome;
        static Material copper;
        static Material gold;
        static Material silver;
        static Material blackPlastic;
        static Material cyanPlastic;
        static Material greenPlastic;
        static Material redPlastic;
        static Material whitePlastic;
        static Material yellowPlastic;
        static Material blackRubber;
        static Material cyanRubber;
        static Material greenRubber;
        static Material redRubber;
        static Material whiteRubber;
        static Material yellowRubber;
    };
}

#endif //MATERIAL_H
