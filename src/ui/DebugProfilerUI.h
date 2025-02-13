#ifndef DEBUG_PROFILER_UI_H
#define DEBUG_PROFILER_UI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../graphics/Renderer.h"
#include "../core/Scene.h"
#include "UIElement.h"

using namespace BG3DRenderer::Graphics;

namespace BG3DRenderer::UI {
    class DebugProfilerUI : public UIElement{
    public:
        DebugProfilerUI();
        ~DebugProfilerUI();

        void Render(Renderer &renderer) override;
    };
}
#endif
