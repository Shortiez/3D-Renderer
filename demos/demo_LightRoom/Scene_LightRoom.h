//
// Created by gotts on 10/02/2025.
//

#ifndef SCENE_LIGHTROOM_H
#define SCENE_LIGHTROOM_H
#include "../../src/core/Scene.h"

namespace BG3DRenderer::Demos::LightRoom
{
    class Scene_LightRoom : public BG3DRenderer::Core::Scene {
    public:
        Scene_LightRoom(Renderer* renderer, Core::Camera* cam, Core::Input* input);
        ~Scene_LightRoom();

        void Start() override;
        void Update(float deltaTime) override;
    };
}




#endif //SCENE_LIGHTROOM_H
