#pragma once

#include "Piece.hpp"

class Queen : public Piece {
public:
    Queen(Color color, ChessTile* tile)
        : Piece(color, tile) {}
    std::vector<ChessTile*> getPossibleMoves() override;
    char                    getSymbol() override { return 'Q'; }
};