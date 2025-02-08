#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <memory>
#include <string>
#include <unordered_map>

#include "Shader.h"

namespace BG3DRenderer::Graphics {
    class ShaderManager {
    private:
        struct ShaderKey {
            std::string vertexPath;
            std::string fragmentPath;

            bool operator==(const ShaderKey& other) const {
                return vertexPath == other.vertexPath &&
                       fragmentPath == other.fragmentPath;
            }
        };

        struct ShaderKeyHash {
            std::size_t operator()(const ShaderKey& key) const {
                return std::hash<std::string>()(key.vertexPath) ^
                       std::hash<std::string>()(key.fragmentPath);
            }
        };

        std::unordered_map<ShaderKey, std::weak_ptr<Shader>, ShaderKeyHash> shaderCache;
        static ShaderManager& getInstance();

        ShaderManager() = default;

    public:
        static std::shared_ptr<Shader> loadShader(const std::string& vertexPath,
                                                  const std::string& fragmentPath);
        static void clearUnused();
    };
}

#endif //SHADERMANAGER_H  