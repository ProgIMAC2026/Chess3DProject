#pragma once

#include <lib/glm/glm.hpp>
#include "../../shader/ShaderProgram.hpp"
#include "../texture/Texture.hpp"
#include "../utils/Transform.hpp"
#include "Mesh.hpp"

class Object {
    Transform transform;

    Mesh*          meshPtr;
    ShaderProgram* shaderProgram;
    Texture*       texture;

public:
    Object() = default;
    Object(const Transform& transform, Mesh* meshPtr, ShaderProgram* shaderProgram, Texture* texture);
    // Getter Setter
    Transform getTransform() const { return transform; }
    void      setTransform(const Transform& transform) { this->transform = transform; }

    Mesh* getMeshPtr() const { return meshPtr; }
    void  setMeshPtr(Mesh* meshPtr);

    ShaderProgram* getShaderProgram() const;
    void           setShaderProgram(ShaderProgram* shaderProgram);

    Texture* getTexture() const;
    void     setTexture(Texture* texture);

    glm::mat4 getModelMatrix() const { return transform.getModelMatrix(); }

    void move(const glm::vec3& translation) { transform.move(translation); }
};