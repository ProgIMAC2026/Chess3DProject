#pragma once

#include "Piece.hpp"

class Rook : public Piece {
public:
    Rook(Color color, ChessTile* tile, std::function<void()> onMoveCallback = []() {})
        : Piece(color, tile, std::move(onMoveCallback))
    {
        _type = PieceType::ROOK;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};