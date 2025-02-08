#version 330 core

uniform vec4 BaseColour;
uniform vec3 LightPos = vec3(1.2f, 1.0f, 2.0f);
uniform vec3 ViewPos;
uniform vec3 LightColor = vec3(1.0, 1.0, 1.0);

out vec4 FragColor;   // Final output color

in vec3 Normal;       // Normal in world space
in vec3 FragPos;      // Position in world space

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * LightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * LightColor;

    vec3 result = (ambient + diffuse) * BaseColour.rgb;

    FragColor = vec4(result, 1.0);
}