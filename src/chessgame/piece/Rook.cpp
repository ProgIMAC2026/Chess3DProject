#include "Rook.hpp"
#include "../chessboard/ChessBoard.hpp"

std::vector<ChessTile*> Rook::getPossibleMoves()
{
    std::vector<ChessTile*> moves;

    // Récupérer la case actuelle
    ChessBoard* board = _currentTilePtr->getBoard();

    if (!_currentTilePtr || !board)
    {
        return moves; // Si la tour n'est pas sur une case valide ou si le plateau est nul
    }

    PositionTile currentPos = _currentTilePtr->getPosition();
    int          x          = currentPos.x;
    int          y          = currentPos.y;

    // direction gauche
    for (int i = x - 1; i >= 0; --i) // Modification ici pour descendre vers la gauche
    {
        ChessTile* leftTile = board->getTile({i, y});
        if (leftTile->getPiece() == nullptr)
        {
            moves.push_back(leftTile); // Case vide
        }
        else if (leftTile->getPiece()->getColor() != getColor()) // Utilisation de getColor()
        {
            moves.push_back(leftTile); // Case occupée par une pièce adverse
            break;                     // La pièce adverse est capturée, on s'arrête ici
        }
        else
        {
            break; // La case est occupée par une pièce alliée, on arrête
        }
    }

    // direction droite
    for (int i = x + 1; i < 8; ++i) // Modification ici pour avancer vers la droite
    {
        ChessTile* rightTile = board->getTile({i, y});
        if (rightTile->getPiece() == nullptr)
        {
            moves.push_back(rightTile); // Case vide
        }
        else if (rightTile->getPiece()->getColor() != getColor()) // Utilisation de getColor()
        {
            moves.push_back(rightTile); // Case occupée par une pièce adverse
            break;                      // La pièce adverse est capturée, on s'arrête ici
        }
        else
        {
            break; // La case est occupée par une pièce alliée, on arrête
        }
    }

    // direction haut
    for (int j = y - 1; j >= 0; --j) // Modification ici pour remonter vers le haut
    {
        ChessTile* topTile = board->getTile({x, j});
        if (topTile->getPiece() == nullptr)
        {
            moves.push_back(topTile); // Case vide
        }
        else if (topTile->getPiece()->getColor() != getColor()) // Utilisation de getColor()
        {
            moves.push_back(topTile); // Case occupée par une pièce adverse
            break;                    // La pièce adverse est capturée, on s'arrête ici
        }
        else
        {
            break; // La case est occupée par une pièce alliée, on arrête
        }
    }

    // direction bas
    for (int j = y + 1; j < 8; ++j) // Modification ici pour descendre vers le bas
    {
        ChessTile* bottomTile = board->getTile({x, j});
        if (bottomTile->getPiece() == nullptr)
        {
            moves.push_back(bottomTile); // Case vide
        }
        else if (bottomTile->getPiece()->getColor() != getColor()) // Utilisation de getColor()
        {
            moves.push_back(bottomTile); // Case occupée par une pièce adverse
            break;                       // La pièce adverse est capturée, on s'arrête ici
        }
        else
        {
            break; // La case est occupée par une pièce alliée, on arrête
        }
    }

    return moves;
}
