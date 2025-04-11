#pragma once

#include "Piece.hpp"

class Knight : public Piece {
public:
    Knight(Color color, ChessTile* tile, std::function<void()> onMoveCallback = []() {})
        : Piece(color, tile, std::move(onMoveCallback))
    {
        _type = PieceType::KNIGHT;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};