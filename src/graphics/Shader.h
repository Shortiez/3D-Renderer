#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h" // Include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <string>
#include <iostream>

namespace BG3DRenderer::Graphics {
    class ShaderManager;  // Forward declaration

    class Shader {
        friend class ShaderManager;
    public:
        unsigned int ID;
        std::string vertexPath;
        std::string fragmentPath;

        ~Shader();

        // Delete copy operations
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        // Allow move operations
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        void Use() const;

        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetColour(const std::string& name, glm::vec4 color) const;
        void SetMat4(const std::string& name, glm::mat4 mat) const;
    private:
        Shader(const std::string& vPath, const std::string& fPath);

        static void checkCompileErrors(unsigned int shader, const std::string& type);
        void compile(const std::string& vertexCode, const std::string& fragmentCode);
    };
}

#endif // SHADER_H