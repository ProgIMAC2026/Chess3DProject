#pragma once

#include "Piece.hpp"

class Knight : public Piece {
public:
    Knight(Color color, ChessTile* tile)
        : Piece(color, tile)
    {
        _type = PieceType::KNIGHT;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};