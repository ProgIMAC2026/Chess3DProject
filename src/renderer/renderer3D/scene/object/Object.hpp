#pragma once

#include <lib/glm/glm.hpp>
#include "../../shader/ShaderProgram.hpp"
#include "../material/Material.hpp"
#include "../utils/Transform.hpp"
#include "Mesh.hpp"

class Object {
    Transform transform;

    Mesh*          meshPtr;
    ShaderProgram* shaderProgram;
    Material       material;

public:
    Object() = default;
    Object(const Transform& transform, Mesh* meshPtr, ShaderProgram* shaderProgram, Material material);
    // Getter Setter
    Transform getTransform() const
    {
        return transform;
    }
    void setTransform(const Transform& transform) { this->transform = transform; }

    Mesh* getMeshPtr() const { return meshPtr; }
    void  setMeshPtr(Mesh* meshPtr);

    ShaderProgram* getShaderProgram() const;
    void           setShaderProgram(ShaderProgram* shaderProgram);

    Material& getMaterial() { return material; }
    void      setMaterial(const Material& material) { this->material = material; }

    glm::mat4 getModelMatrix() const { return transform.getModelMatrix(); }

    void move(const glm::vec3& translation) { transform.move(translation); }
};