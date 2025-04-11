#include "Object.hpp"

Object::Object(const Transform& transform, Mesh* meshPtr, ShaderProgram* shaderProgram, Material baseMaterial)
    : transform(transform), meshPtr(meshPtr), shaderProgram(shaderProgram), baseMaterial(baseMaterial) {}
