#pragma once

#include "chessboard/ChessBoard.hpp"
#include "chessboard/ChessTile.hpp"
class ChessGame {
    ChessBoard _chessBoard;
    ChessTile* _selectedTile = nullptr;

public:
    ChessGame();
    ~ChessGame();
    void start();
    void update();
    void end();

    ChessBoard& getChessBoard() { return _chessBoard; }

    ChessTile* getSelectedTile() { return _selectedTile; }
    void       setSelectedTile(ChessTile* tile) { _selectedTile = tile; }
};