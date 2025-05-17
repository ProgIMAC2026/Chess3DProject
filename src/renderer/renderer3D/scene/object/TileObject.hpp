#pragma once

#include "Object.hpp"
#include "chessgame/ChessGame.hpp"
#include "chessgame/chessboard/ChessTile.hpp"
#include "chessgame/piece/Piece.hpp"
#include "renderer/renderer3D/scene/Scene.hpp"

class TileObject : public Object {
    ChessTile* tile = nullptr; // Pointer to the tile associated with this object (if any)
public:
    TileObject() = default;
    TileObject(const Transform& transform, Mesh* meshPtr, ShaderProgram* shaderProgram, Material baseMaterial, ChessTile* tile = nullptr)
        : Object(transform, meshPtr, shaderProgram, baseMaterial), tile(tile)
    {
        onClick = [tile](Object* obj) {
            if (tile != nullptr)
            {
                ChessGame*   chessgame = tile->getBoard()->getChessGame();
                PositionTile position  = tile->getPosition();

                if (chessgame->isPossibleMove(tile) && tile->getPiece() == nullptr)
                {
                    chessgame->movePieceTo(chessgame->getSelectedTile()->getPiece(), tile);
                }
            }
        };
    };

    ChessTile* getTile() const { return tile; }
    void       setTile(ChessTile* tile)
    {
        this->tile = tile;
    }

    Material getMaterial() override
    {
        if (tile == nullptr)
            return Object::getMaterial();

        ChessGame* chessgame = tile->getBoard()->getChessGame();

        PositionTile position = tile->getPosition();

        if (chessgame->isPossibleMove(tile) && tile->getPiece() == nullptr)
            return {
                glm::vec3(0.f, 1.f, 0.f),
                glm::vec3(0.4f),
                glm::vec3(2.f),
                5.f
            };

        return Material(
            (position.x + position.y) % 2 == 0 ? glm::vec3(1.f, 1.f, 1.f) : glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.4f),
            glm::vec3(2.f),
            5.f
        );
    }
};