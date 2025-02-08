#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"

namespace BG3DRenderer::Graphics
{
    Shader::Shader(const std::string& vPath, const std::string& fPath)
            : ID(0), vertexPath(vPath), fragmentPath(fPath)
    {
        std::string vertexCode, fragmentCode;
        std::ifstream vShaderFile, fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            compile(vShaderStream.str(), fShaderStream.str());
        }
        catch(const std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
    }

    Shader::~Shader() {
        if (ID != 0) {
            glDeleteProgram(ID);
        }
    }

    Shader::Shader(Shader&& other) noexcept
            : ID(other.ID),
              vertexPath(std::move(other.vertexPath)),
              fragmentPath(std::move(other.fragmentPath))
    {
        other.ID = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept {
        if (this != &other) {
            if (ID != 0) {
                glDeleteProgram(ID);
            }

            ID = other.ID;
            vertexPath = std::move(other.vertexPath);
            fragmentPath = std::move(other.fragmentPath);

            other.ID = 0;
        }
        return *this;
    }

    void Shader::compile(const std::string& vertexCode, const std::string& fragmentCode)
    {
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::Use() const {
        glUseProgram(ID);
    }

    // Uniform setters implementation...
    void Shader::SetBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::SetInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::SetColour(const std::string& name, Colour color) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), color.r, color.g, color.b, color.a);
    }

    void Shader::SetMat4(const std::string& name, glm::mat4 mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
        int success;
        char infoLog[1024];

        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type
                          << "\n" << infoLog << std::endl;
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type
                          << "\n" << infoLog << std::endl;
            }
        }
    }
}
