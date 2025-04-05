#pragma once

#include "../piece/Color.hpp"
#include "lib/glm/glm.hpp"

using PositionTile = glm::vec<2, unsigned int>;

class Piece;
class ChessBoard;

class ChessTile {
    PositionTile position;
    Piece*       _piecePtr = nullptr;
    ChessBoard*  _boardPtr;

public:
    ChessTile(PositionTile position, ChessBoard* boardPtr)
        : position(position), _boardPtr(boardPtr) {}
    PositionTile getPosition() { return position; }

    Piece*      getPiece() { return _piecePtr; }
    ChessBoard* getBoard() { return _boardPtr; }

    template<typename PieceType>
    void createPiece(Color color)
    {
        _piecePtr = new PieceType(color, this);
    }

    void setPiece(Piece* piece) { _piecePtr = piece; }
    void removePiece() { _piecePtr = nullptr; }

    bool hasPiece() const { return _piecePtr != nullptr; }
    bool isEmpty() const { return _piecePtr == nullptr; }
};