#include <glm/glm.hpp>

namespace BG3DRenderer::Graphics {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TextureCoords;

        Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
                : Position(pos), Normal(norm), TextureCoords(tex) {}

        Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
                : Position(x, y, z), Normal(nx, ny, nz), TextureCoords(u, v) {}
    };
}