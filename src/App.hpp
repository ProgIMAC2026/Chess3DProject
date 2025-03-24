#pragma once

#include "chessgame/ChessGame.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/Window.hpp"
class App {
private:
    /* data */
    ChessGame _chessGame;
    Renderer  _renderer;
    Window    _window;

public:
    App();
    ~App();
    void run();
};