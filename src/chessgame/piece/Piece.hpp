#pragma once

#include <vector>
#include "../chessboard/ChessTile.hpp"
#include "Color.hpp"

// Abstract Piece class
class Piece {
protected:
    Color      _color;
    ChessTile* _currentTilePtr;

    void setTile(ChessTile* tile)
    {
        tile->setPiece(this);
        _currentTilePtr->removePiece();
        _currentTilePtr = tile;
    }

public:
    Piece(Color color, ChessTile* tile)
        : _color(color), _currentTilePtr(tile)
    {
        _currentTilePtr->setPiece(this);
    }
    virtual std::vector<ChessTile*> getPossibleMoves() = 0;
    virtual PositionTile            getPosition() { return _currentTilePtr->getPosition(); }

    void moveTo(ChessTile* newTile) { setTile(newTile); }

    Color        getColor() const { return _color; }
    virtual char getSymbol() { return 'P'; }
};