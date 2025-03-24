#include "Renderer3D.hpp"

void Renderer3D::init()
{
    glfwInit();
};

Renderer3D::Renderer3D()
    : scene(), window(400, 400)
{
    init();
    window.create();
    glfwMakeContextCurrent(window.getWindow());
};

void Renderer3D::render(ChessGame& chessGame)
{
    while (!window.shouldClose())
    {
        window.pollEvents();
        window.swapBuffers();
    }
};