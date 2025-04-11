#pragma once

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Color color, ChessTile* tile, std::function<void()> onMoveCallback = []() {})
        : Piece(color, tile, std::move(onMoveCallback))
    {
        _type = PieceType::PAWN;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};