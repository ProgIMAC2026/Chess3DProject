#include "Object.hpp"

Object::Object(const Transform& transform, Mesh* meshPtr, ShaderProgram* shaderProgram, Material material)
    : transform(transform), meshPtr(meshPtr), shaderProgram(shaderProgram), material(material) {}
