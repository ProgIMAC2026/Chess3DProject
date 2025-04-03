#include "Bishop.hpp"
#include "../chessboard/ChessBoard.hpp"

std::vector<ChessTile*> Bishop::getPossibleMoves()
{
    std::vector<ChessTile*> moves;
    ChessBoard*             board      = _currentTilePtr->getBoard();
    PositionTile            currentPos = _currentTilePtr->getPosition();
    int                     x          = currentPos.x;
    int                     y          = currentPos.y;

    // Directions diagonales
    const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, // haut gauche
        {-1, 1},  // haut droite
        {1, -1},  // bas gauche
        {1, 1}    // bas droite
    };

    for (const auto& dir : directions)
    {
        int dx   = dir.first;
        int dy   = dir.second;
        int newX = x + dx;
        int newY = y + dy;

        while (newX >= 0 && newY >= 0 && newX < 8 && newY < 8)
        {
            ChessTile* targetTile  = board->getTile({newX, newY});
            Piece*     targetPiece = targetTile->getPiece();

            if (targetPiece == nullptr)
            {
                moves.push_back(targetTile); // Case vide
            }
            else
            {
                if (targetPiece->getColor() != _color)
                {
                    moves.push_back(targetTile); // Capture possible
                }
                break; // Arrêter si une pièce bloque le chemin
            }
            newX += dx;
            newY += dy;
        }
    }
    return moves;
}