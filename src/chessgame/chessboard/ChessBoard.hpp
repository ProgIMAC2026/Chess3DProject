#pragma once

#include "ChessTile.hpp"
class ChessBoard {
    ChessTile* tiles[8][8];

public:
    ChessBoard();
    ~ChessBoard();

    ChessTile* getTile(PositionTile position) { return tiles[position.x][position.y]; }
};