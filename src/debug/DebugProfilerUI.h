#ifndef DEBUG_PROFILER_UI_H
#define DEBUG_PROFILER_UI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../graphics/Renderer.h"
#include "../core/Scene.h"

using namespace BG3DRenderer::Graphics;

namespace BG3DRenderer::Debug {
    class DebugProfilerUI {
    public:
        DebugProfilerUI(GLFWwindow *window);
        ~DebugProfilerUI();

        void Render(Scene &scene, Renderer &renderer);

    private:
        void NewFrame();

        void EndFrame();
    };
}
#endif
