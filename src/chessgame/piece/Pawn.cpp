#include "Pawn.hpp"
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

    PositionTile direction = (_color == Color::BLACK) ? PositionTile(1, 0) : PositionTile(-1, 0);

    if ((currentPos + direction).x >= 0 && (currentPos + direction).x < 8) // Vérifier les limites du plateau
    {
        ChessTile* frontTile = board->getTile(currentPos + direction);
        if (frontTile && !frontTile->getPiece())
        {
            moves.push_back(frontTile);

            // Vérifier si le pion peut avancer de deux cases
            if (currentPos.x == ((_color == Color::BLACK) ? 1 : 6))
            {
                ChessTile* doubleMoveTile = board->getTile(currentPos + direction * (unsigned int)(2));
                if (doubleMoveTile && !doubleMoveTile->getPiece())
                {
                    moves.push_back(doubleMoveTile);
                }
            }
        }
    }

    // Vérifier les captures diagonales
    for (PositionTile dirDiagonal : {PositionTile(0, 1), PositionTile(0, -1)})
    {
        PositionTile diagPosition = direction + dirDiagonal + currentPos;

        if (diagPosition.x >= 0 && diagPosition.x < 8 && diagPosition.y >= 0 && diagPosition.y < 8) // Vérifier les limites du plateau
        {
            ChessTile* diagonalTile = board->getTile(diagPosition);
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

    // if (x == passantRow)
    // {
    //     for (int dx : {-1, 1}) // Vérification des cases diagonales gauche et droite
    //     {
    //         int newY = y + dx;         // Déplacement gauche-droite
    //         if (newY >= 0 && newY < 8) // Vérifier les limites du plateau
    //         {
    //             ChessTile* adjacentTile = board->getTile({x, newY});
    //             if (adjacentTile)
    //             {
    //                 Piece* adjacentPiece = adjacentTile->getPiece();
    //                 if (adjacentPiece && adjacentPiece->getType() == PieceType::PAWN && adjacentPiece->getColor() != _color)
    //                 {
    //                     // Vérification de la possibilité de prise en passant
    //                     if (board->isEnPassantAvailable(adjacentTile))
    //                     {
    //                         ChessTile* enPassantTile = board->getTile({x + direction, newY}); // Case de prise en passant
    //                         if (enPassantTile)
    //                         {
    //                             moves.push_back(enPassantTile); // Ajout de la case de prise en passant
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    return moves;
}
