#pragma once

#include "Piece.hpp"

class Bishop : public Piece {
public:
    Bishop(Color color, ChessTile* tile)
        : Piece(color, tile) {}
    std::vector<ChessTile*> getPossibleMoves() override;
    char                    getSymbol() override { return 'B'; }
};