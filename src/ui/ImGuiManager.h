// ImGuiManager.h

#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace BG3DRenderer::UI{
    class ImGuiManager {
    public:
        ImGuiManager(GLFWwindow* window);
        ~ImGuiManager();

        void NewFrame();
        void Render();
    };
}
#endif // IMGUIMANAGER_H