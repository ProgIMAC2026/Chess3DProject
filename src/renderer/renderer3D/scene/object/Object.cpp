#include "Object.hpp"

Object::Object(const Transform& transform, Mesh* meshPtr, ShaderProgram* shaderProgram, Texture* texture)
    : transform(transform), meshPtr(meshPtr), shaderProgram(shaderProgram), texture(texture) {}
