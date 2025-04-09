#version 330

uniform float gObjectIndex;

in vec3 FragPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vec3(gObjectIndex), 1.f);
} 