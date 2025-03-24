#pragma once

#include "../Renderer.hpp"

class TerminalRenderer : public Renderer {
public:
    void render(ChessGame& chessGame) override;
};