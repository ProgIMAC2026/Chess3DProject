#include "TerminalRenderer.hpp"
#include <iostream>
#include "../../chessgame/piece/Piece.hpp"

void TerminalRenderer::render(ChessGame& chessGame)
{
    while (true)
    {
        // Clear terminal
        system("cls");
        // Render chess board in terminal
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                auto tile = chessGame.getChessBoard().getTile({i, j});
                if (tile->getPiece() != nullptr)
                {
                    std::cout << tile->getPiece()->getSymbol();
                }
                else
                {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
    }
}