#include "Queen.hpp"
#include "../chessboard/ChessBoard.hpp"

std::vector<ChessTile*> Queen::getPossibleMoves()
{
    std::vector<ChessTile*> moves;

    ChessBoard* board = _currentTilePtr->getBoard();

    if (!_currentTilePtr || !board)
    {
        return moves; // Vérifier si la pièce est sur une case valide et si le plateau existe
    }

    PositionTile currentPos = _currentTilePtr->getPosition();
    int          x          = currentPos.x;
    int          y          = currentPos.y;

    // Liste des directions : diagonales + orthogonales
    const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, // Haut-gauche
        {-1, 1},  // Haut-droite
        {1, -1},  // Bas-gauche
        {1, 1},   // Bas-droite
        {-1, 0},  // Gauche
        {1, 0},   // Droite
        {0, -1},  // Haut
        {0, 1}    // Bas
    };

    for (const auto& dir : directions)
    {
        int dx = dir.first;
        int dy = dir.second;

        int newX = x + dx;
        int newY = y + dy;

        // Parcourir dans une direction jusqu'à atteindre une limite ou une pièce
        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
        {
            ChessTile* targetTile = board->getTile({newX, newY});
            if (targetTile)
            {
                Piece* targetPiece = targetTile->getPiece();

                // Si la case est vide
                if (!targetPiece)
                {
                    moves.push_back(targetTile); // Ajouter la case vide aux mouvements possibles
                }
                else
                {
                    // Si la case contient une pièce adverse
                    if (targetPiece->getColor() != _color)
                    {
                        moves.push_back(targetTile); // Ajouter la case pour la capture
                    }
                    break; // On ne peut pas sauter par-dessus une pièce
                }
            }

            // Avancer dans la direction
            newX += dx;
            newY += dy;
        }
    }

    return moves;
}
