#pragma once

#include "Piece.hpp"
#include "PieceType.hpp"

class Bishop : public Piece {
public:
    Bishop(Color color, ChessTile* tile)
        : Piece(color, tile)
    {
        _type = PieceType::BISHOP;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};