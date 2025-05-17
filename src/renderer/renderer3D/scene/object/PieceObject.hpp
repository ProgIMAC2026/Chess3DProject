#pragma once

#include "Object.hpp"
#include "chessgame/chessboard/ChessBoard.hpp"
#include "chessgame/piece/Piece.hpp"
#include "renderer/renderer3D/scene/Scene.hpp"
#include "renderer/renderer3D/scene/material/Material.hpp"

class PieceObject : public Object {
    Piece* piece      = nullptr; // Pointer to the piece associated with this object (if any)
    bool   _canRender = true;    // Flag to indicate if the object can be rendered
public:
    PieceObject() = default;
    PieceObject(const Transform& transform, Mesh* meshPtr, ShaderProgram* shaderProgram, Material baseMaterial, Piece* piece = nullptr)
        : Object(transform, meshPtr, shaderProgram, baseMaterial), piece(piece)
    {
        onClick = [this, piece](Object* obj) {
            if (piece != nullptr)
            {
                ChessGame* chessgame = piece->getCurrentTile()->getBoard()->getChessGame();

                if (chessgame->isPossibleMove(piece->getCurrentTile()))
                {
                    chessgame->movePieceTo(chessgame->getSelectedTile()->getPiece(), piece->getCurrentTile());
                    _canRender = false; // Disable rendering after moving the piece
                    chessgame->clearSelectedTile();
                }

                if (chessgame->isTileSelected(piece->getCurrentTile()))
                {
                    chessgame->clearSelectedTile();
                }
                else
                {
                    if (piece->getColor() == chessgame->getCurrentTurn())
                        chessgame->setSelectedTile(piece->getCurrentTile());
                }
            }
        };
        piece->setOnMoveCallback(
            [this, piece]() {
                this->setTransform(
                    {Scene::positionTileTo3DPosition(piece->getCurrentTile()->getPosition()),
                     glm::vec3(0.f),
                     glm::vec3(1.f)
                    }
                );
            }
        );
    }

    Piece* getPiece() const
    {
        return piece;
    }
    void setPiece(Piece* piece)
    {
        this->piece = piece;
    }

    bool canRender() const
    {
        return piece != nullptr && Object::canRender() && _canRender;
    }

    Material getMaterial() override
    {
        if (piece == nullptr)
            return Object::getMaterial();

        if (piece->getCurrentTile()->getBoard()->getChessGame()->isTileSelected(piece->getCurrentTile()))
        {
            return {
                glm::vec3(0.f, 1.f, 0.f),
                glm::vec3(0.4f),
                glm::vec3(2.f),
                5.f
            };
        }

        if (piece->getCurrentTile()->getBoard()->getChessGame()->isPossibleMove(piece->getCurrentTile()))
        {
            return {
                glm::vec3(1.f, 0.f, 0.f),
                glm::vec3(0.4f),
                glm::vec3(2.f),
                5.f
            };
        }

        if (piece->getColor() == Color::BLACK)
        {
            return {
                glm::vec3(1.f, 1.f, 1.f),
                glm::vec3(1.f, 1.f, 1.f),
                glm::vec3(1.f, 1.f, 1.f),
                32.f
            };
        }
        else
        {
            return {
                glm::vec3(0.f, 0.f, 0.f),
                glm::vec3(0.2f),
                glm::vec3(0.2f),
                32.f
            };
        }
    }
};