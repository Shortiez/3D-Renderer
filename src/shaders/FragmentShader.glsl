#version 330 core

out vec4 FragColor;   // Final output color

uniform vec4 BaseColour;

void main()
{
    // Apply texture and color to the fragment
    FragColor = vec4(BaseColour);
}