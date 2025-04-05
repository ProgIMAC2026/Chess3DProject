#pragma once

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Color color, ChessTile* tile)
        : Piece(color, tile)
    {
        _type = PieceType::PAWN;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};