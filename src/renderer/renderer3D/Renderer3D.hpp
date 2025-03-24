#pragma once

#include "../Renderer.hpp"
#include "Window.hpp"
#include "scene/Scene.hpp"

class Renderer3D : public Renderer {
private:
    Scene  scene;
    Window window;
    void   init();

public:
    Renderer3D();

    void render(ChessGame& chessGame) override;
};