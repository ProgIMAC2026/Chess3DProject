#include "Object.hpp"

Object::Object(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, Mesh* meshPtr, ShaderProgram* shaderProgram, Texture* texture)
    : position(position), rotation(rotation), scale(scale), meshPtr(meshPtr), shaderProgram(shaderProgram), texture(texture) {}
