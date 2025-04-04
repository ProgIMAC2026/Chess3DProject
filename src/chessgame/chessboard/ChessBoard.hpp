#pragma once

#include "ChessTile.hpp"

class ChessBoard {
    ChessTile* tiles[8][8];

public:
    ChessBoard();
    ~ChessBoard();

    ChessTile* getTile(PositionTile position) { return tiles[position.x][position.y]; }

    ChessTile* lastMovedPawnTile = nullptr;

    void setLastMovedPawnTile(ChessTile* tile)
    {
        lastMovedPawnTile = tile;
    }

    bool isEnPassantAvailable(ChessTile* tile) const
    {
        return lastMovedPawnTile == tile;
    }

    template<typename PieceType>
    void createPiece(Color color, ChessTile* tile)
    {
        tile->createPiece<PieceType>(color);
    }
};