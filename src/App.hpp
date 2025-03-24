#pragma once

#include "chessgame/ChessGame.hpp"
#include "renderer/Renderer.hpp"
class App {
private:
    /* data */
    ChessGame _chessGame;
    Renderer  _renderer;

public:
    App();
    ~App();
    void run();
};