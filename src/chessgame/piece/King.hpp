#pragma once

#include <utility>
#include "Piece.hpp"


class King : public Piece {
public:
    King(Color color, ChessTile* tile, std::function<void()> onMoveCallback = []() {})
        : Piece(color, tile, std::move(onMoveCallback))
    {
        _type = PieceType::KING;
    }
    std::vector<ChessTile*> getPossibleMoves() override;
};