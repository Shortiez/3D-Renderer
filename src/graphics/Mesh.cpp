#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Mesh.h"
#include <iostream>
#include <ostream>
#include <glm/ext/matrix_transform.hpp>

namespace BG3DRenderer::Graphics {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Material> material)
            : vertices(std::move(vertices))
            , indices(std::move(indices))
            , material(material ? material : Material::GetDefaultMaterial())
            , VAO(0), VBO(0), EBO(0)
            , isInitialized(std::make_shared<bool>(true)) {

        createBuffers();
    }

    Mesh::~Mesh() {
        cleanupBuffers();
    }

    // Copy constructor
    Mesh::Mesh(const Mesh& other)
            : isInitialized(std::make_shared<bool>(true)),
              vertices(other.vertices),
              indices(other.indices),
              material(other.material) {
        createBuffers();
    }

    // Move constructor
    Mesh::Mesh(Mesh&& other) noexcept
            : vertices(std::move(other.vertices)),
              indices(std::move(other.indices)),
              material(std::move(other.material)),
              VAO(other.VAO),
              VBO(other.VBO),
              EBO(other.EBO),
              isInitialized(std::move(other.isInitialized)) {
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
    }

    // Copy assignment
    Mesh& Mesh::operator=(const Mesh& other) {
        if (this != &other) {
            // Clean up existing resources
            if (VAO != 0) {
                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
                glDeleteBuffers(1, &EBO);
            }

            vertices = other.vertices;
            indices = other.indices;
            material = other.material;

            isInitialized = std::make_shared<bool>(true);

            createBuffers();
        }
        return *this;
    }

    // Move assignment
    Mesh& Mesh::operator=(Mesh&& other) noexcept {
        if (this != &other) {
            // Clean up existing resources
            if (VAO != 0) {
                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
                glDeleteBuffers(1, &EBO);
            }

            vertices = std::move(other.vertices);
            indices = std::move(other.indices);
            material = std::move(other.material);

            VAO = other.VAO;
            VBO = other.VBO;
            EBO = other.EBO;

            isInitialized = std::move(other.isInitialized);

            other.VAO = 0;
            other.VBO = 0;
            other.EBO = 0;
        }
        return *this;
    }

    void Mesh::createBuffers() {
        // Create Buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // Bind and set vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // Bind and set element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Set vertex attribute pointers
        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoords));

        // Unbind VAO (it's always a good practice to unbind any buffer/array to prevent strange bugs)
        glBindVertexArray(0);

        // Check for any OpenGL errors
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error during mesh creation: " << err << std::endl;
        }
    }

    void Mesh::cleanupBuffers() {
        if (VAO != 0) {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }
    }

    void Mesh::DrawMesh(std::shared_ptr<Shader> shader) {
        if (!*isInitialized || VAO == 0) {
            std::cerr << "Attempting to draw uninitialized mesh" << std::endl;
            return;
        }

        material->UpdateMaterial(shader);
        shader->Use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        GLenum err;
        // Check for any OpenGL errors
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error during draw (end): " << err << std::endl;
        }
    }

    void Mesh::SetMaterial(std::shared_ptr<Material> newMaterial) {
        material = newMaterial ? newMaterial : Material::GetDefaultMaterial();
    }

    std::shared_ptr<Material> Mesh::GetMaterial() {
        return material;
    }
}
