#pragma once

#include "Piece.hpp"

class Knight : public Piece {
public:
    Knight(Color color, ChessTile* tile)
        : Piece(color, tile) {}
    std::vector<ChessTile*> getPossibleMoves() override;
    char                    getSymbol() override { return 'K'; }
};