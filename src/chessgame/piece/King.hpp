#pragma once

#include "Piece.hpp"

class King : public Piece {
public:
    King(Color color, ChessTile* tile)
        : Piece(color, tile) {}
    std::vector<ChessTile*> getPossibleMoves() override;
    char                    getSymbol() override { return 'K'; }
};