#pragma once

#include <vector>
#include "../chessboard/ChessTile.hpp"

// Abstract Piece class
class Piece {
protected:
    ChessTile* _currentTilePtr;

    void setTile(ChessTile* tile)
    {
        tile->setPiece(this);
        _currentTilePtr->removePiece();
        _currentTilePtr = tile;
    }

public:
    // virtual std::vector<ChessTile> getPosibleMoves() = 0;
    virtual PositionTile getPosition() { return _currentTilePtr->getPosition(); }

    void moveTo(ChessTile* newTile) { setTile(newTile); }

    virtual char getSymbol() { return 'P'; }
};