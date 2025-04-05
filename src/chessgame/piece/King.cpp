#include "King.hpp"
#include "../chessboard/ChessBoard.hpp"

std::vector<ChessTile*> King::getPossibleMoves()
{
    std::vector<ChessTile*> moves;
    ChessBoard*             board = _currentTilePtr->getBoard();

    if (!_currentTilePtr || !board)
    {
        return moves; // Vérifier si le roi est sur une case valide et si le plateau existe
    }

    PositionTile currentPos = _currentTilePtr->getPosition();
    int          x          = currentPos.x;
    int          y          = currentPos.y;

    // Toutes les directions possibles pour un roi
    const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
    };

    // Parcourir toutes les directions
    for (const auto& dir : directions)
    {
        int newX = x + dir.first;
        int newY = y + dir.second;

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
