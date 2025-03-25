#pragma once

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Color color, ChessTile* tile)
        : Piece(color, tile) {}
    std::vector<ChessTile*> getPossibleMoves() override;
    char                    getSymbol() override { return 'P'; }
};