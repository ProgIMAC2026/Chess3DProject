#include "App.hpp"

App::App()
    : _chessGame() {}

App::~App() {}

void App::run()
{
    // Start the game
    _chessGame.start();

    _rendererPtr->render(_chessGame);

    // End the game
    _chessGame.end();
}