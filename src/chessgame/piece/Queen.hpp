#pragma once

#include "Piece.hpp"

class Queen : public Piece {
public:
    Queen(Color color, ChessTile* tile, std::function<void()> onMoveCallback = []() {})
        : Piece(color, tile, std::move(onMoveCallback))
    {
        _type = PieceType::QUEEN;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};