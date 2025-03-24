#pragma once

#include "Window.hpp"
#include "chessgame/ChessGame.hpp"
class Renderer {
private:
    void init();

public:
    Renderer() = default;
    Renderer(Window& window);
    ~Renderer();

    void render(ChessGame& chessGame);
};