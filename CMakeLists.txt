cmake_minimum_required(VERSION 3.30)
project(3D_Renderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()

# Include directories
include_directories(include)  # Your includes
include_directories(third-party/imgui)  # Dear ImGui

# Manually add ImGui source files
set(IMGUI_SOURCES
        third-party/imgui/imgui.cpp
        third-party/imgui/imgui_demo.cpp
        third-party/imgui/imgui_draw.cpp
        third-party/imgui/imgui_impl_glfw.cpp
        third-party/imgui/imgui_impl_opengl3.cpp
        third-party/imgui/imgui_tables.cpp
        third-party/imgui/imgui_widgets.cpp
)

# Manually add source files
set(SOURCES
        src/main.cpp

        src/core/Application.cpp
        src/core/Window.cpp
        src/core/SceneManager.cpp
        src/core/Scene.cpp
        src/core/SceneObject.cpp
        src/core/Camera.cpp
        src/core/Input.cpp
        src/core/Transform.cpp

        src/graphics/Material.cpp
        src/graphics/Mesh.cpp
        src/graphics/MeshLibrary.cpp
        src/graphics/Renderer.cpp
        src/graphics/Shader.cpp
        src/graphics/ShaderManager.cpp
        src/graphics/Vertex.cpp
        src/graphics/Colour.cpp

        src/lighting/Light.cpp
        src/lighting/DirectionalLight.cpp
        src/lighting/SpotLight.cpp
        src/lighting/PointLight.cpp

        src/ui/ImGuiManager.cpp
        src/ui/UIElement.cpp
        src/ui/App_TopBarUI.cpp
        src/ui/DebugProfilerUI.cpp
)

set(DEMOS
        demos/demo_SpinningCube/Scene_SpinningCube.cpp
        demos/demo_LightRoom/Scene_LightRoom.cpp
)

# Create the executable
add_executable(3D_Renderer ${SOURCES} ${IMGUI_SOURCES} ${DEMOS} src/renderdoc_app.h src/glad.c)

# Platform-specific GLFW setup
if (APPLE)
    find_package(glfw3 REQUIRED)
    target_link_libraries(3D_Renderer glfw "-framework OpenGL")
elseif (WIN32)
    # GLFW setup for MinGW on Windows
    set(GLFW_ROOT "D:/ProgrammingLanguages/C++/Packages/glfw")
    set(GLFW_INCLUDE_DIR "${GLFW_ROOT}/include")
    set(GLFW_LIB_DIR "${GLFW_ROOT}/lib-mingw-w64")  # Make sure this path matches

    # GLM setup
    set(GLM_ROOT "D:/ProgrammingLanguages/C++/Packages/glm")
    include_directories(${GLM_ROOT})
    include_directories(${GLFW_INCLUDE_DIR})

    # Link GLFW and OpenGL libraries
    link_directories(${GLFW_LIB_DIR})

    # Ensure correct linking
    target_link_libraries(3D_Renderer ${GLFW_LIB_DIR}/libglfw3.a opengl32)
endif()
