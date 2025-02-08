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

        std::shared_ptr<Material> material;

        void createBuffers();
        void cleanupBuffers();
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Material> material = Material::GetDefaultMaterial());
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

        void SetMaterial(std::shared_ptr<Material> material);
        std::shared_ptr<Material> GetMaterial();
    };
}

#endif //MESH_H
