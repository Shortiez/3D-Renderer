cmake_minimum_required(VERSION 3.30)
project(3D_Renderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Find GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# Include directories
include_directories(include)  # Your includes
include_directories(third-party/imgui)  # Include Dear ImGui

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
        src/core/Scene.cpp
        src/core/SceneObject.cpp
        src/core/Camera.cpp
        src/core/Input.cpp

        src/graphics/Material.cpp
        src/graphics/Mesh.cpp
        src/graphics/MeshLibrary.cpp
        src/graphics/Renderer.cpp
        src/graphics/ShaderUtility.cpp
        src/graphics/Vertex.cpp

        src/debug/DebugProfilerUI.cpp
)

# Create the executable
add_executable(3D_Renderer ${SOURCES} ${IMGUI_SOURCES} src/glad.c)

# Link GLFW and OpenGL (macOS uses -framework OpenGL)
target_link_libraries(3D_Renderer glfw "-framework OpenGL")