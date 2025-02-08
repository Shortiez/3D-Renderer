#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;     // Model transformation matrix
uniform mat4 view;      // View transformation matrix
uniform mat4 projection; // Projection transformation matrix

void main()
{
    // Calculate final position of the vertex
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}