#pragma once

#include <vector>
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

    std::vector<Piece*> getPieces() const
    {
        std::vector<Piece*> pieces;
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (tiles[i][j]->hasPiece())
                {
                    pieces.push_back(tiles[i][j]->getPiece());
                }
            }
        }
        return pieces;
    }
};