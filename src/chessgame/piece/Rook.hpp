#pragma once

#include "Piece.hpp"

class Rook : public Piece {
public:
    Rook(Color color, ChessTile* tile)
        : Piece(color, tile) {}
    std::vector<ChessTile*> getPossibleMoves() override;
    char                    getSymbol() override { return 'R'; }
};