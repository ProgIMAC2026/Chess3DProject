#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
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

    void renderScene();
};