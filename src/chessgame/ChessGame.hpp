#pragma once

#include "chessboard/ChessBoard.hpp"
class ChessGame {
    ChessBoard chessBoard;

public:
    ChessGame();
    ~ChessGame();
    void start();
    void update();
    void end();

    ChessBoard& getChessBoard() { return chessBoard; }
};