//
// Created by Ben Gotts on 25/01/2025.
//

#include "Material.h"

#include <iostream>

namespace BG3DRenderer::Graphics
{
    Material::Material() {
        ambient = Colour::White();
        diffuse = Colour::White();
        specular = Colour::White();
        shininess = 32.0f;
    }

    Material::Material(Colour ambient, Colour diffuse, Colour specular, float shininess) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
    }

    void Material::UpdateMaterial(std::shared_ptr<Shader> shader) {
        if (!shader) {
            std::cerr << "Material::UpdateMaterial - Shader is null!" << std::endl;
            return;
        }

        shader->Use();

        shader->SetVec3("material.ambient", ambient.ToVec3());
        shader->SetVec3("material.diffuse", diffuse.ToVec3());
        shader->SetVec3("material.specular", specular.ToVec3());
        shader->SetFloat("material.shininess", shininess);

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error in Material::UpdateMaterial: " << err << std::endl;
        }
    }

    void Material::SetColour(Colour colour) {
        ambient = colour;
        diffuse = colour;
    }

    void Material::SetAmbient(Colour ambient) {
        this->ambient = ambient;
    }

    void Material::SetDiffuse(Colour diffuse) {
        this->diffuse = diffuse;
    }

    void Material::SetSpecular(Colour specular) {
        this->specular = specular;
    }

    void Material::SetShininess(float shininess) {
        this->shininess = shininess;
    }

    std::shared_ptr<Material> Material::GetDefaultMaterial() {
        return std::make_shared<Material>();
    }

    // Static Material definitions
    Material Material::emerald = Material(Colour(0.0215f, 0.1745f, 0.0215f), Colour(0.07568f, 0.61424f, 0.07568f), Colour(0.633f, 0.727811f, 0.633f), 0.6f);
    Material Material::jade = Material(Colour(0.135f, 0.2225f, 0.1575f), Colour(0.54f, 0.89f, 0.63f), Colour(0.316228f, 0.316228f, 0.316228f), 0.1f);
    Material Material::obsidian = Material(Colour(0.05375f, 0.05f, 0.06625f), Colour(0.18275f, 0.17f, 0.22525f), Colour(0.332741f, 0.328634f, 0.346435f), 0.3f);
    Material Material::pearl = Material(Colour(0.25f, 0.20725f, 0.20725f), Colour(1.0f, 0.829f, 0.829f), Colour(0.296648f, 0.296648f, 0.296648f), 0.088f);
    Material Material::ruby = Material(Colour(0.1745f, 0.01175f, 0.01175f), Colour(0.61424f, 0.04136f, 0.04136f), Colour(0.727811f, 0.626959f, 0.626959f), 0.6f);
    Material Material::turquoise = Material(Colour(0.1f, 0.18725f, 0.1745f), Colour(0.396f, 0.74151f, 0.69102f), Colour(0.297254f, 0.30829f, 0.306678f), 0.1f);
    Material Material::brass = Material(Colour(0.329412f, 0.223529f, 0.027451f), Colour(0.780392f, 0.568627f, 0.113725f), Colour(0.992157f, 0.941176f, 0.807843f), 0.21794872f);
    Material Material::bronze = Material(Colour(0.2125f, 0.1275f, 0.054f), Colour(0.714f, 0.4284f, 0.18144f), Colour(0.393548f, 0.271906f, 0.166721f), 0.2f);
    Material Material::chrome = Material(Colour(0.25f, 0.25f, 0.25f), Colour(0.4f, 0.4f, 0.4f), Colour(0.774597f, 0.774597f, 0.774597f), 0.6f);
    Material Material::copper = Material(Colour(0.19125f, 0.0735f, 0.0225f), Colour(0.7038f, 0.27048f, 0.0828f), Colour(0.256777f, 0.137622f, 0.086014f), 0.1f);
    Material Material::gold = Material(Colour(0.24725f, 0.1995f, 0.0745f), Colour(0.75164f, 0.60648f, 0.22648f), Colour(0.628281f, 0.555802f, 0.366065f), 0.4f);
    Material Material::silver = Material(Colour(0.19225f, 0.19225f, 0.19225f), Colour(0.50754f, 0.50754f, 0.50754f), Colour(0.508273f, 0.508273f, 0.508273f), 0.4f);
    Material Material::blackPlastic = Material(Colour(0.0f, 0.0f, 0.0f), Colour(0.01f, 0.01f, 0.01f), Colour(0.5f, 0.5f, 0.5f), 0.25f);
    Material Material::cyanPlastic = Material(Colour(0.0f, 0.1f, 0.06f), Colour(0.0f, 0.50980392f, 0.50980392f), Colour(0.50196078f, 0.50196078f, 0.50196078f), 0.25f);
    Material Material::greenPlastic = Material(Colour(0.0f, 0.0f, 0.0f), Colour(0.1f, 0.35f, 0.1f), Colour(0.45f, 0.55f, 0.45f), 0.25f);
    Material Material::redPlastic = Material(Colour(0.0f, 0.0f, 0.0f), Colour(0.5f, 0.0f, 0.0f), Colour(0.7f, 0.6f, 0.6f), 0.25f);
    Material Material::whitePlastic = Material(Colour(0.0f, 0.0f, 0.0f), Colour(0.55f, 0.55f, 0.55f), Colour(0.7f, 0.7f, 0.7f), 0.25f);
    Material Material::yellowPlastic = Material(Colour(0.0f, 0.0f, 0.0f), Colour(0.5f, 0.5f, 0.0f), Colour(0.6f, 0.6f, 0.5f), 0.25f);
    Material Material::blackRubber = Material(Colour(0.02f, 0.02f, 0.02f), Colour(0.01f, 0.01f, 0.01f), Colour(0.4f, 0.4f, 0.4f), 0.078125f);
    Material Material::cyanRubber = Material(Colour(0.0f, 0.05f, 0.05f), Colour(0.4f, 0.5f, 0.5f), Colour(0.04f, 0.7f, 0.7f), 0.078125f);
    Material Material::greenRubber = Material(Colour(0.0f, 0.05f, 0.0f), Colour(0.4f, 0.5f, 0.4f), Colour(0.04f, 0.7f, 0.04f), 0.078125f);
    Material Material::redRubber = Material(Colour(0.05f, 0.0f, 0.0f), Colour(0.5f, 0.4f, 0.4f), Colour(0.7f, 0.04f, 0.04f), 0.078125f);
    Material Material::whiteRubber = Material(Colour(0.05f, 0.05f, 0.05f), Colour(0.5f, 0.5f, 0.5f), Colour(0.7f, 0.7f, 0.7f), 0.078125f);
    Material Material::yellowRubber = Material(Colour(0.05f, 0.05f, 0.0f), Colour(0.5f, 0.5f, 0.4f), Colour(0.7f, 0.7f, 0.04f), 0.078125f);
}
