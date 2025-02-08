// RenderDocIntegration.h
#ifndef RENDERDOC_INTEGRATION_H
#define RENDERDOC_INTEGRATION_H

// Prevent std::byte and ensure this is before any other includes
#define _HAS_STD_BYTE 0
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#ifdef _WIN32  // Ensure this code only compiles on Windows

// Order of includes is important here
#include <Windows.h>
#include <../src/renderdoc_app.h>

namespace BG3DRenderer::Debug {
    class RenderDocIntegration {
    public:
        static RenderDocIntegration& getInstance();

        bool initialize();
        void startCapture();
        void endCapture();
        void captureFrame();

    private:
        RenderDocIntegration();
        ~RenderDocIntegration();

        HMODULE renderDocModule;
        RENDERDOC_API_1_1_2* rdocApi;
    };
}

#endif // _WIN32
#endif // RENDERDOC_INTEGRATION_H