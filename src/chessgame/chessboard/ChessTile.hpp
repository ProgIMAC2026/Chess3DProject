#pragma once

#include "lib/glm/glm.hpp"

using PositionTile = glm::vec<2, unsigned int>;

class Piece;

class ChessTile {
    PositionTile position;
    Piece*       _piecePtr = nullptr;

public:
    ChessTile(PositionTile position)
        : position(position) {}
    PositionTile getPosition() { return position; }

    Piece* getPiece() { return _piecePtr; }

    void setPiece(Piece* piece) { _piecePtr = piece; }
    void removePiece() { _piecePtr = nullptr; }
};