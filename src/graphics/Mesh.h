#ifndef MESH_H
#define MESH_H
#include "glad/glad.h"

#include "Material.h"
#include "Shader.h"
#include "Vertex.cpp"
#include <vector>
#include <memory>

namespace BG3DRenderer::Graphics{
    class Mesh {
    private:
        std::shared_ptr<bool> isInitialized;

        GLuint VBO{0}, VAO{0}, EBO{0};
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        Material fallbackMat;
        Material& material = fallbackMat;

        void createBuffers();
        void cleanupBuffers();
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        ~Mesh();

        // Copy constructor
        Mesh(const Mesh& other);
        // Move constructor
        Mesh(Mesh&& other) noexcept;
        // Copy assignment
        Mesh& operator=(const Mesh& other);
        // Move assignment
        Mesh& operator=(Mesh&& other) noexcept;

        void DrawMesh(std::shared_ptr<Shader> shader);

        void SetMaterial(Material& material);
    };
}

#endif //MESH_H
