#include "App.hpp"
#include "renderer/Window.hpp"

App::App()
    : _window(800, 600), _chessGame()
{
    _renderer = Renderer(_window);
}

App::~App() {}

void App::run()
{
    // Start the game
    _chessGame.start();

    // This is where the main loop will be
    while (!_window.shouldClose())
    {
        // Poll events, update the game, render the game, swap buffers
        _window.pollEvents();

        // Update the game
        _chessGame.update();

        // Render the game
        _renderer.render(_chessGame);

        // Swap buffers
        _window.swapBuffers();
    }

    // End the game
    _chessGame.end();
}