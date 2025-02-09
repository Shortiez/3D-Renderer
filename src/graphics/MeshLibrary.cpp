//
// Created by Ben Gotts on 25/01/2025.
//

#include "MeshLibrary.h"

namespace BG3DRenderer::Graphics{

    Mesh MeshLibrary::Quad(float width, float height) {
        std::vector<Vertex> vertices = {
                {{-width, -height, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{ width, -height, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                {{ width,  height, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
                {{-width,  height, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
        };

        std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3 };

        return {vertices, indices};
    }

    Mesh MeshLibrary::Cube(float size)
    {
        float halfSize = size / 2;

        std::vector<Vertex> vertices = {
            // Front face
            {{-halfSize, -halfSize,  halfSize}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
            {{ halfSize, -halfSize,  halfSize}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
            {{ halfSize,  halfSize,  halfSize}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
            {{-halfSize,  halfSize,  halfSize}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},

            // Back face
            {{-halfSize, -halfSize, -halfSize}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ halfSize, -halfSize, -halfSize}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ halfSize,  halfSize, -halfSize}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-halfSize,  halfSize, -halfSize}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},

            // Left face
            {{-halfSize, -halfSize, -halfSize}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
            {{-halfSize, -halfSize,  halfSize}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
            {{-halfSize,  halfSize,  halfSize}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
            {{-halfSize,  halfSize, -halfSize}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},

            // Right face
            {{ halfSize, -halfSize, -halfSize}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
            {{ halfSize, -halfSize,  halfSize}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
            {{ halfSize,  halfSize,  halfSize}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
            {{ halfSize,  halfSize, -halfSize}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},

            // Top face
            {{-halfSize,  halfSize, -halfSize}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
            {{ halfSize,  halfSize, -halfSize}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
            {{ halfSize,  halfSize,  halfSize}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
            {{-halfSize,  halfSize,  halfSize}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},

            // Bottom face
            {{-halfSize, -halfSize, -halfSize}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},
            {{ halfSize, -halfSize, -halfSize}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
            {{ halfSize, -halfSize,  halfSize}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
            {{-halfSize, -halfSize,  halfSize}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}}
        };

        std::vector<unsigned int> indices = {
            0, 1, 2, 0, 2, 3,  // Front
            4, 5, 6, 4, 6, 7,  // Back
            8, 9, 10, 8, 10, 11, // Left
            12, 13, 14, 12, 14, 15, // Right
            16, 17, 18, 16, 18, 19, // Top
            20, 21, 22, 20, 22, 23  // Bottom
        };

        return {vertices, indices};
    }

    Mesh MeshLibrary::Sphere(float radius, int res) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (int lat = 0; lat <= res; ++lat) {
            float theta = lat * M_PI / res;  // Latitude (0 to pi)
            float sinTheta = sinf(theta);
            float cosTheta = cosf(theta);

            for (int lon = 0; lon <= res; ++lon) {
                float phi = lon * 2 * M_PI / res;  // Longitude (0 to 2pi)
                float sinPhi = sinf(phi);
                float cosPhi = cosf(phi);

                glm::vec3 position = {
                        radius * cosPhi * sinTheta,
                        radius * cosTheta,
                        radius * sinPhi * sinTheta
                };

                glm::vec3 normal = glm::normalize(position);

                glm::vec2 texCoords = {
                        (float)lon / res,
                        (float)lat / res
                };

                vertices.push_back({position, normal, texCoords});
            }
        }

        // Generate indices
        for (int lat = 0; lat < res; ++lat) {
            for (int lon = 0; lon < res; ++lon) {
                int first = lat * (res + 1) + lon;
                int second = first + res + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }

        return {vertices, indices};
    }
}