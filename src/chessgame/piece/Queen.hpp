#pragma once

#include "Piece.hpp"

class Queen : public Piece {
public:
    Queen(Color color, ChessTile* tile)
        : Piece(color, tile)
    {
        _type = PieceType::QUEEN;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};