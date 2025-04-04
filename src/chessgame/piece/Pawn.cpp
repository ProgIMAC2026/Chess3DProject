#include "Pawn.hpp"
#include <iostream>
#include "../chessboard/ChessBoard.hpp"

std::vector<ChessTile*> Pawn::getPossibleMoves()
{
    std::vector<ChessTile*> moves;
    ChessBoard*             board = _currentTilePtr->getBoard();

    if (!_currentTilePtr || !board)
    {
        return moves; // Vérifier si le pion est sur une case valide et si le plateau existe
    }

    PositionTile currentPos = _currentTilePtr->getPosition();
    int          x          = currentPos.x;
    int          y          = currentPos.y;

    int direction  = (_color == Color::WHITE) ? 1 : -1;
    int startRow   = (_color == Color::WHITE) ? 1 : 6;
    int passantRow = (_color == Color::WHITE) ? 4 : 3;

    // Vérifier la case devant
    if (x + direction >= 0 && x + direction < 8) // Vérifier les limites du plateau
    {
        ChessTile* frontTile = board->getTile({x + direction, y});
        if (frontTile && !frontTile->getPiece())
        {
            moves.push_back(frontTile);

            // Vérifier si le pion peut avancer de deux cases
            if (y == startRow)
            {
                ChessTile* doubleMoveTile = board->getTile({x + 2 * direction, y});
                if (doubleMoveTile && !doubleMoveTile->getPiece())
                {
                    moves.push_back(doubleMoveTile);
                }
            }
        }
    }

    // Vérifier les captures diagonales
    for (int dx : {-1, 1})
    {
        int newX = x + direction;
        int newY = y + dx;

        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) // Vérifier les limites du plateau
        {
            ChessTile* diagonalTile = board->getTile({newX, newY});
            if (diagonalTile)
            {
                Piece* targetPiece = diagonalTile->getPiece();
                if (targetPiece && targetPiece->getColor() != _color)
                {
                    moves.push_back(diagonalTile); // Capture d'une pièce adverse
                }
            }
        }
    }

    if (x == passantRow)
    {
        for (int dx : {-1, 1}) // Vérification des cases diagonales gauche et droite
        {
            int newY = y + dx;         // Déplacement gauche-droite
            if (newY >= 0 && newY < 8) // Vérifier les limites du plateau
            {
                ChessTile* adjacentTile = board->getTile({x, newY});
                if (adjacentTile)
                {
                    Piece* adjacentPiece = adjacentTile->getPiece();
                    if (adjacentPiece && adjacentPiece->isPawn() && adjacentPiece->getColor() != _color)
                    {
                        // Vérification de la possibilité de prise en passant
                        if (board->isEnPassantAvailable(adjacentTile))
                        {
                            ChessTile* enPassantTile = board->getTile({x + direction, newY}); // Case de prise en passant
                            if (enPassantTile)
                            {
                                moves.push_back(enPassantTile); // Ajout de la case de prise en passant
                            }
                        }
                    }
                }
            }
        }
    }

    return moves;
}
