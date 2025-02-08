// RenderDocIntegration.cpp
// These defines must come before ANY includes
#define _HAS_STD_BYTE 0
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "RenderDocIntegration.h"
#include <iostream>

#ifdef _WIN32

#include <filesystem>

namespace BG3DRenderer::Debug {

    RenderDocIntegration& RenderDocIntegration::getInstance() {
        static RenderDocIntegration instance;
        return instance;
    }

    RenderDocIntegration::RenderDocIntegration()
        : renderDocModule(nullptr), rdocApi(nullptr) {}

    RenderDocIntegration::~RenderDocIntegration() {
        if (renderDocModule) {
            FreeLibrary(renderDocModule);
        }
    }

    bool RenderDocIntegration::initialize() {
        std::string renderdoc_path;

        // 1️⃣ Check your custom installation path first (Modify as needed)
        std::filesystem::path customPath = "D:/RenderDoc/renderdoc.dll";
        if (std::filesystem::exists(customPath)) {
            renderdoc_path = customPath.string();
        }

        // 2️⃣ If not found, check standard "C:\Program Files\RenderDoc"
        if (renderdoc_path.empty()) {
            char buffer[MAX_PATH];
            if (GetEnvironmentVariableA("ProgramFiles", buffer, MAX_PATH)) {
                std::filesystem::path defaultPath = std::filesystem::path(buffer) / "RenderDoc" / "renderdoc.dll";
                if (std::filesystem::exists(defaultPath)) {
                    renderdoc_path = defaultPath.string();
                }
            }
        }

        // 3️⃣ Fallback: Try to load from system PATH
        if (renderdoc_path.empty()) {
            renderdoc_path = "renderdoc.dll";  // This will check the PATH
        }

        // 4️⃣ Attempt to load RenderDoc DLL
        renderDocModule = LoadLibraryA(renderdoc_path.c_str());
        if (!renderDocModule) {
            std::cerr << "RenderDoc DLL not found! Checked: " << renderdoc_path << std::endl;
            return false;
        }

        // 5️⃣ Get API function
        pRENDERDOC_GetAPI rdocGetAPI = (pRENDERDOC_GetAPI)GetProcAddress(renderDocModule, "RENDERDOC_GetAPI");
        if (!rdocGetAPI || rdocGetAPI(eRENDERDOC_API_Version_1_6_0, (void**)&rdocApi) != 1) {
            std::cerr << "Failed to retrieve RenderDoc API!" << std::endl;
            FreeLibrary(renderDocModule);
            return false;
        }

        std::cout << "RenderDoc successfully initialized from: " << renderdoc_path << std::endl;
        return true;
    }

    void RenderDocIntegration::startCapture() {
        if (rdocApi) {
            rdocApi->StartFrameCapture(nullptr, nullptr);
            std::cout << "RenderDoc capture started." << std::endl;
        } else {
            std::cerr << "RenderDoc is not initialized!" << std::endl;
        }
    }

    void RenderDocIntegration::endCapture() {
        if (rdocApi) {
            rdocApi->EndFrameCapture(nullptr, nullptr);
            std::cout << "RenderDoc capture ended." << std::endl;
        } else {
            std::cerr << "RenderDoc is not initialized!" << std::endl;
        }
    }

    void RenderDocIntegration::captureFrame() {
        if (initialize()) {  // Ensure RenderDoc is ready
            std::cout << "Capturing single frame..." << std::endl;
            startCapture();
            endCapture();
        }
    }

} // namespace BG3DRenderer::Debug

#endif // _WIN32