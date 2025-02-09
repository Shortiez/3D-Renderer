#version 330 core

uniform vec4 BaseColour; // Base colour of the object
uniform vec3 LightPos; // Light position
uniform vec3 ViewPos; // Camera position
uniform vec3 LightColour; // Light colour

out vec4 FragColour;   // Final output color

in vec3 Normal;       // Normal in world space
in vec3 FragPos;      // Position in world space

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * LightColour;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * LightColour;

    vec3 result = (ambient + diffuse) * BaseColour.rgb;

    FragColour = vec4(result, 1.0);
}