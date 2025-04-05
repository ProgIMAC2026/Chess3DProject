#pragma once

#include "Piece.hpp"

class King : public Piece {
public:
    King(Color color, ChessTile* tile)
        : Piece(color, tile)
    {
        _type = PieceType::KING;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};