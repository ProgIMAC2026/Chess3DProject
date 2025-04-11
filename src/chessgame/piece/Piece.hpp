#pragma once

#include <functional>
#include <utility>
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

    std::function<void()> _onMoveCallback = []() {};

    void setTile(ChessTile* tile)
    {
        tile->setPiece(this);
        _currentTilePtr->removePiece();
        _currentTilePtr = tile;
    }

public:
    Piece(Color color, ChessTile* tile, std::function<void()> onMoveCallback = []() {})
        : _color(color), _currentTilePtr(tile), _onMoveCallback(std::move(onMoveCallback))
    {
        _currentTilePtr->setPiece(this);
    }
    virtual std::vector<ChessTile*> getPossibleMoves() = 0;
    virtual PositionTile            getPosition() { return _currentTilePtr->getPosition(); }

    virtual Color     getColor() { return _color; }
    virtual PieceType getType() { return _type; }

    virtual ChessTile* getCurrentTile() { return _currentTilePtr; }

    void moveTo(ChessTile* newTile)
    {
        setTile(newTile);
        _onMoveCallback();
    }

    void setOnMoveCallback(std::function<void()> onMoveCallback)
    {
        _onMoveCallback = std::move(onMoveCallback);
    }
};