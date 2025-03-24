#pragma once

#include "Window.hpp"
#include "chessgame/ChessGame.hpp"
#include "scene/Scene.hpp"
class Renderer {
private:
    Scene scene;

    void init();

public:
    Renderer() = default;
    Renderer(Window& window);
    ~Renderer();

    void render(ChessGame& chessGame);
};