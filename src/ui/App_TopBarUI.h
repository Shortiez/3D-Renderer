// App_TopBarUI.h

#ifndef APP_TOPBARUI_H
#define APP_TOPBARUI_H

#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "UIElement.h"
#include "../core/Scene.h"

#include "../../demos/demo_SpinningCube/Scene_SpinningCube.h"
#include "../../demos/demo_LightRoom/Scene_LightRoom.h"

struct DemoSceneInfo {
    std::string name;
    std::function<std::unique_ptr<BG3DRenderer::Core::Scene>()> createFunc;
};

namespace BG3DRenderer::UI
{
    class App_TopBarUI : public UIElement{
    private:
        std::vector<DemoSceneInfo> demoScenes{
            {"Spinning Cube", []() {
                    return std::make_unique<BG3DRenderer::Demos::SpinningCube::Scene_SpinningCube>(nullptr, nullptr, nullptr);
            }},
            {"Light Room", []() {
                return std::make_unique<BG3DRenderer::Demos::LightRoom::Scene_LightRoom>(nullptr, nullptr, nullptr);
            }}
        };
    public:
        App_TopBarUI();
        ~App_TopBarUI();
        void Render() override;
    };
}

#endif // APP_TOPBARUI_H