#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ShaderUtility.h"

namespace BG3DRenderer::Graphics {

    ShaderUtility::ShaderUtility(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode, fragmentCode;
        std::ifstream vertexShaderFile, fragmentShaderFile;
        vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            vertexShaderFile.open(vertexPath);
            fragmentShaderFile.open(fragmentPath);

            std::stringstream vertexShaderStream, fragmentShaderStream;
            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            vertexShaderFile.close();
            fragmentShaderFile.close();

            vertexCode = vertexShaderStream.str();
            fragmentCode = fragmentShaderStream.str();
        } catch (std::ifstream::failure &e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
        }

        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        unsigned int vertexShader, fragmentShader;
        int success;
        char infoLog[512];

        std::cout << vShaderCode << std::endl;
        std::cout << fShaderCode << std::endl;

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "VERTEX");

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
        glCompileShader(fragmentShader);
        checkCompileErrors(fragmentShader, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void ShaderUtility::Use() const {
        if (ID == 0) {
            std::cerr << "Shader program is not initialized!" << std::endl;
            return;
        }
        glUseProgram(ID);
    }

    void ShaderUtility::SetBool(const std::string &name, bool value) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location == -1) {
            std::cout << "Error: Could not find uniform location for " << name << std::endl;
            return;
        }
        glUniform1i(location, (int)value);
        std::cout << "SetBool: " << name << " = " << value << std::endl;
    }

    void ShaderUtility::SetInt(const std::string &name, int value) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location == -1) {
            std::cout << "Error: Could not find uniform location for " << name << std::endl;
            return;
        }
        glUniform1i(location, value);
        std::cout << "SetInt: " << name << " = " << value << std::endl;
    }

    void ShaderUtility::SetFloat(const std::string &name, float value) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location == -1) {
            std::cout << "Error: Could not find uniform location for " << name << std::endl;
            return;
        }
        glUniform1f(location, value);
        std::cout << "SetFloat: " << name << " = " << value << std::endl;
    }

    void ShaderUtility::SetColour(const std::string &name, glm::vec4 color) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location == -1) {
            std::cout << "Error: Could not find uniform location for " << name << std::endl;
            return;
        }
        glUniform4f(location, color.r, color.g, color.b, color.a);
        std::cout << "SetColour: " << name << " = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
    }

    void ShaderUtility::SetMat4(const std::string &name, glm::mat4 mat) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location == -1) {
            std::cout << "Error: Could not find uniform location for " << name << std::endl;
            return;
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
        std::cout << "SetMat4: " << name << " matrix set" << std::endl;
    }

}