#pragma once

#include <lib/glm/glm.hpp>
#include "../../shader/ShaderProgram.hpp"
#include "../texture/Texture.hpp"
#include "Mesh.hpp"

class Object {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Mesh*          meshPtr;
    ShaderProgram* shaderProgram;
    Texture*       texture;

public:
    Object() = default;
    Object(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, Mesh* meshPtr, ShaderProgram* shaderProgram, Texture* texture);
    // Getter Setter
    glm::vec3 getPosition() const;
    void      setPosition(const glm::vec3& position);
    glm::vec3 getRotation() const;
    void      setRotation(const glm::vec3& rotation);
    glm::vec3 getScale() const;
    void      setScale(const glm::vec3& scale);

    Mesh* getMeshPtr() const { return meshPtr; }
    void  setMeshPtr(Mesh* meshPtr);

    ShaderProgram* getShaderProgram() const;
    void           setShaderProgram(ShaderProgram* shaderProgram);

    Texture* getTexture() const;
    void     setTexture(Texture* texture);
};