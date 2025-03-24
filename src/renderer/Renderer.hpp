#pragma once

#include "chessgame/ChessGame.hpp"
class Renderer {
public:
    Renderer();
    ~Renderer();
    void render(ChessGame& chessGame);
};