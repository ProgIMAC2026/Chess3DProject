#pragma once

#include <functional>
#include <lib/glm/glm.hpp>
#include <utility>
#include "../../shader/ShaderProgram.hpp"
#include "../material/Material.hpp"
#include "../utils/Transform.hpp"
#include "Mesh.hpp"
#include "chessgame/ChessGame.hpp"
#include "chessgame/chessboard/ChessTile.hpp"
#include "chessgame/piece/Piece.hpp"

class Object {
protected:
    Transform transform;

    Mesh*          meshPtr;
    ShaderProgram* shaderProgram;
    Material       baseMaterial;

    // Callback function for when the object is clicked
    std::function<void(Object*)> onClick;

public:
    Object() = default;
    Object(const Transform& transform, Mesh* meshPtr, ShaderProgram* shaderProgram, Material baseMaterial);

    // Getter Setter
    Transform getTransform() const { return transform; }
    void      setTransform(const Transform& transform) { this->transform = transform; }

    Mesh* getMeshPtr() const { return meshPtr; }
    void  setMeshPtr(Mesh* meshPtr);

    ShaderProgram* getShaderProgram() const;
    void           setShaderProgram(ShaderProgram* shaderProgram);

    virtual Material getMaterial() { return baseMaterial; }

    void setMaterial(Material material) { this->baseMaterial = material; }

    glm::mat4 getModelMatrix() const { return transform.getModelMatrix(); }

    void move(const glm::vec3& translation) { transform.move(translation); }

    virtual bool canRender() const { return meshPtr != nullptr && shaderProgram != nullptr; }

    void click()
    {
        if (onClick)
            onClick(this);
    }
};