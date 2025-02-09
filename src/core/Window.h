// Window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

namespace BG3DRenderer::Core {
    class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        bool ShouldClose();
        void SwapBuffers();
        GLFWwindow* GetWindow() { return window; }

        // Add these new methods
        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        float GetAspectRatio();
    private:
        GLFWwindow* window;
        int width;
        int height;

        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    };
}
#endif //WINDOW_H