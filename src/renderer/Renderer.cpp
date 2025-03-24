#include "Renderer.hpp"
#include "GLFW/glfw3.h"
#include "Window.hpp"

Renderer::Renderer(Window& window)
{
    init();
    window.create();
    glfwMakeContextCurrent(window.getWindow());
};

Renderer::~Renderer() {};

void Renderer::init()
{
    glfwInit();
};

void Renderer::render(ChessGame& chessGame) {};