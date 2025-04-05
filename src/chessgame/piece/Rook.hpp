#pragma once

#include "Piece.hpp"

class Rook : public Piece {
public:
    Rook(Color color, ChessTile* tile)
        : Piece(color, tile)
    {
        _type = PieceType::ROOK;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};