//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef MESHLIBRARY_H
#define MESHLIBRARY_H

#include "Mesh.h"

namespace BG3DRenderer::Graphics {
    class MeshLibrary {
    public:
        static Mesh Quad(float width, float height);
        static Mesh Cube(float size);
        static Mesh Sphere(float radius, int res);
    };
}
#endif //MESHLIBRARY_H
