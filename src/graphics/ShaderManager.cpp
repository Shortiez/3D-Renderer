//
// Created by gotts on 05/02/2025.
//

#include "ShaderManager.h"

namespace BG3DRenderer::Graphics {

    // ShaderManager implementation
    ShaderManager& ShaderManager::getInstance() {
        static ShaderManager instance;
        return instance;
    }

    std::shared_ptr<Shader> ShaderManager::loadShader(const std::string& vertexPath,
                                                    const std::string& fragmentPath)
    {
        auto& instance = getInstance();
        ShaderKey key{vertexPath, fragmentPath};

        // Check if shader exists and is still valid
        auto it = instance.shaderCache.find(key);
        if (it != instance.shaderCache.end()) {
            if (auto existingShader = it->second.lock()) {
                return existingShader;
            }
            // If weak_ptr is expired, remove it from cache
            instance.shaderCache.erase(it);
        }

        // Create new shader
        auto shader = std::shared_ptr<Shader>(new Shader(vertexPath, fragmentPath));
        instance.shaderCache[key] = shader;
        return shader;
    }

    void ShaderManager::clearUnused() {
        auto& instance = getInstance();
        for (auto it = instance.shaderCache.begin(); it != instance.shaderCache.end();) {
            if (it->second.expired()) {
                it = instance.shaderCache.erase(it);
            } else {
                ++it;
            }
        }
    }

}