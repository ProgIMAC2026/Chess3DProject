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

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
};

void Renderer3D::render(ChessGame& chessGame)
{
    scene.init();
    while (!window.shouldClose())
    {
        window.pollEvents();
        window.swapBuffers();
    }
};