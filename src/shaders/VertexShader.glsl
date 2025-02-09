#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;     // Model transformation matrix
uniform mat4 view;      // View transformation matrix
uniform mat4 projection; // Projection transformation matrix

out vec3 FragPos; // For passing the position to the fragment shader
out vec3 Normal; // For passing the normal to the fragment shader
out vec2 TexCoords;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;

    // Calculate final position of the vertex
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}