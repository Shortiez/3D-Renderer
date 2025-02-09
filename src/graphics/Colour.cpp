//
// Created by gotts on 08/02/2025.
//

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Colour {
    float r;
    float g;
    float b;
    float a = 1.0f;

    Colour() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    Colour(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {}
    Colour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
    Colour(glm::vec3 colour) : r(colour.r), g(colour.g), b(colour.b), a(1.0f) {}
    Colour(glm::vec4 colour) : r(colour.r), g(colour.g), b(colour.b), a(colour.a) {}

    glm::vec3 ToVec3() { return glm::vec3(r, g, b); }
    glm::vec4 ToVec4() { return glm::vec4(r, g, b, a); }

    // List Of Colour Constants
    static Colour White() { return Colour(1.0f, 1.0f, 1.0f, 1.0f); }
    static Colour Black() { return Colour(0.0f, 0.0f, 0.0f, 1.0f); }
    static Colour Red() { return Colour(1.0f, 0.0f, 0.0f, 1.0f); }
    static Colour Green() { return Colour(0.0f, 1.0f, 0.0f, 1.0f); }
    static Colour Blue() { return Colour(0.0f, 0.0f, 1.0f, 1.0f); }
    static Colour Yellow() { return Colour(1.0f, 1.0f, 0.0f, 1.0f); }
    static Colour Cyan() { return Colour(0.0f, 1.0f, 1.0f, 1.0f); }
    static Colour Magenta() { return Colour(1.0f, 0.0f, 1.0f, 1.0f); }
    static Colour Grey() { return Colour(0.5f, 0.5f, 0.5f, 1.0f); }
    static Colour LightGrey() { return Colour(0.75f, 0.75f, 0.75f, 1.0f); }
    static Colour DarkGrey() { return Colour(0.25f, 0.25f, 0.25f, 1.0f); }
    static Colour Transparent() { return Colour(0.0f, 0.0f, 0.0f, 0.0f); }
};
