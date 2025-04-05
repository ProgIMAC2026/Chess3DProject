#pragma once

#include <vector>
#include "../chessboard/ChessTile.hpp"
#include "Color.hpp"
#include "PieceType.hpp"

// Abstract Piece class
class Piece {
protected:
    Color      _color;
    PieceType  _type;
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

    virtual Color     getColor() { return _color; }
    virtual PieceType getType() { return _type; }

    void moveTo(ChessTile* newTile) { setTile(newTile); }

    Color        getColor() const { return _color; }
    virtual bool isPawn() const { return false; }
    virtual char getSymbol() { return 'P'; }
};