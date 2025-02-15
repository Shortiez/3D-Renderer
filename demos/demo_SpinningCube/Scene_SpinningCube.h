//
// Created by gotts on 10/02/2025.
//

#ifndef SCENE_SPINNINGCUBE_H
#define SCENE_SPINNINGCUBE_H
#include "../../src/core/Scene.h"

namespace BG3DRenderer::Demos{
    class Scene_SpinningCube : public BG3DRenderer::Core::Scene {
    public:
        Scene_SpinningCube(Renderer* renderer, Core::Camera* cam, Core::Input* input);
        ~Scene_SpinningCube();

        void Start() override;
        void Update(float deltaTime) override;
    };
}



#endif //SCENE_SPINNINGCUBE_H
