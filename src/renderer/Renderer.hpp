#pragma once
#include "chessgame/ChessGame.hpp"
class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    virtual void render(ChessGame& chessGame) = 0;
};