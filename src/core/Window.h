//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

namespace BG3DRenderer::Core {
    class Window {
    public:
        Window(int width, int height, const char *title);

        ~Window();

        bool ShouldClose();

        void SwapBuffers();

        GLFWwindow *GetWindow() {
            return window;
        }

    private:
        GLFWwindow *window;
    };
}
#endif //WINDOW_H
