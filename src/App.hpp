#pragma once

#include "chessgame/ChessGame.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/renderer3D/Renderer3D.hpp"
#include "renderer/rendererTerminal/TerminalRenderer.hpp"

class App {
private:
    ChessGame _chessGame;
    Renderer* _rendererPtr = new TerminalRenderer();

public:
    App();
    ~App();
    void run();
};