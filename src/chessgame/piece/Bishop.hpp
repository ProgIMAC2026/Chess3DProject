#pragma once

#include "Piece.hpp"
#include "PieceType.hpp"

class Bishop : public Piece {
public:
    Bishop(Color color, ChessTile* tile, std::function<void()> onMoveCallback = []() {})
        : Piece(color, tile, std::move(onMoveCallback))
    {
        _type = PieceType::BISHOP;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};