#include "ChessBoard.hpp"
#include "../piece/Piece.hpp"

ChessBoard::ChessBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tiles[i][j] = new ChessTile({i, j});
        }
    }

    // Set pieces
    tiles[3][4]->setPiece(new Piece());
}

ChessBoard::~ChessBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            delete tiles[i][j];
            tiles[i][j] = nullptr;
        }
    }
}