#pragma once

#include "chessgame/ChessGame.hpp"
class App {
private:
    /* data */
    ChessGame _chessGame;

public:
    App();
    ~App();
    void run();
};