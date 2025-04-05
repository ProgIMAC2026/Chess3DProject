#include "Knight.hpp"
#include "../chessboard/ChessBoard.hpp"

std::vector<ChessTile*> Knight::getPossibleMoves()
{
    std::vector<ChessTile*> moves;
    ChessBoard*             board = _currentTilePtr->getBoard();

    // Récupérer la case actuelle
    if (!_currentTilePtr || !board)
    {
        return moves; // Si la pièce n'est pas sur une case valide ou si le plateau est nul
    }

    PositionTile currentPos = _currentTilePtr->getPosition();
    int          x          = currentPos.x;
    int          y          = currentPos.y;

    // Liste des déplacements possibles pour un cavalier
    const std::vector<std::pair<int, int>> directions = {
        {-2, -1}, {-2, 1}, // Mouvement vers le haut-gauche et haut-droite
        {2, -1},
        {2, 1}, // Mouvement vers le bas-gauche et bas-droite
        {-1, -2},
        {1, -2}, // Mouvement gauche-haut et gauche-bas
        {-1, 2},
        {1, 2} // Mouvement droite-haut et droite-bas
    };

    // Parcourir chaque déplacement
    for (const auto& move : directions)
    {
        int newX = x + move.first;
        int newY = y + move.second;

        // Vérifier si la position est dans les limites du plateau
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
        {
            ChessTile* targetTile = board->getTile({newX, newY});

            if (targetTile)
            {
                Piece* targetPiece = targetTile->getPiece();

                // Ajouter la case si elle est vide ou contient une pièce ennemie
                if (!targetPiece || targetPiece->getColor() != _color)
                {
                    moves.push_back(targetTile);
                }
            }
        }
    }

    return moves;
}