#pragma once

#include <vector>
#include "chessboard/ChessBoard.hpp"
#include "chessboard/ChessTile.hpp"
#include "chessgame/piece/Piece.hpp"
#include "piece/Color.hpp"
class ChessGame {
    ChessBoard _chessBoard;

    Color _currentTurn = Color::WHITE; // The current turn (white or black)

    ChessTile* _selectedTile = nullptr;

public:
    ChessGame();
    ~ChessGame();
    void start();
    void update();
    void end();

    void setSelectedTile(ChessTile* tile) { _selectedTile = tile; }
    bool isTileSelected(ChessTile* tile) const { return _selectedTile == tile; }

    void clearSelectedTile() { _selectedTile = nullptr; }

    // Getters
    ChessBoard& getChessBoard() { return _chessBoard; }
    Color       getCurrentTurn() const { return _currentTurn; }
    void        switchTurn()
    {
        if (_currentTurn == Color::BLACK)
            _currentTurn = Color::WHITE;
        else
            _currentTurn = Color::BLACK;
    }

    ChessTile* getSelectedTile() const { return _selectedTile; }
    bool       isTileSelected() const { return _selectedTile != nullptr; }

    ChessTile* getTileAtPosition(PositionTile position) { return _chessBoard.getTile(position); }

    std::vector<Piece*> getPieces() const { return _chessBoard.getPieces(); }

    void movePieceTo(Piece* piece, ChessTile* tile)
    {
        if (piece == nullptr || tile == nullptr)
            return;
        if (piece->getCurrentTile() == tile)
            return;
        piece->moveTo(tile);
        switchTurn();
    }

    bool isPossibleMove(const ChessTile* tile) const
    {
        if (tile == nullptr)
            return false;
        if (_selectedTile == nullptr)
            return false;
        if (_selectedTile->getPiece() == nullptr)
            return false;

        Piece*                  piece         = _selectedTile->getPiece();
        std::vector<ChessTile*> possibleMoves = piece->getPossibleMoves();
        return std::find(possibleMoves.begin(), possibleMoves.end(), tile) != possibleMoves.end();
    }
};