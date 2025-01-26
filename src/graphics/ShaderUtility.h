#ifndef SHADERUTILITY_H
#define SHADERUTILITY_H

#include "glad/glad.h" // Include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <string>
#include <iostream>

namespace BG3DRenderer::Graphics {
	class ShaderUtility {
	public:
		unsigned int ID;

		ShaderUtility(const char* vertexPath, const char* fragmentPath);

		void Use() const;
		void SetBool(const std::string &name, bool value) const;
		void SetInt(const std::string &name, int value) const;
		void SetFloat(const std::string &name, float value) const;
		void SetColour(const std::string &name, glm::vec4 color) const;
		void SetMat4(const std::string &name, glm::mat4 mat) const;
	private:
		static void checkCompileErrors(unsigned int shader, std::string type) {
			int success;
			char infoLog[1024];
			if (type != "PROGRAM") {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
							  << "\n -- --------------------------------------------------- -- " << std::endl;
				}
			} else {
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
					std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
							  << "\n -- --------------------------------------------------- -- " << std::endl;
				}
			}
		}
	};
}

#endif // SHADERUTILITY_H