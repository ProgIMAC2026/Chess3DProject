#version 330

layout (location = 0) in vec3 Position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 FragPos;

void main()
{
    FragPos = vec3(modelMatrix * vec4(Position, 1.0));
    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}