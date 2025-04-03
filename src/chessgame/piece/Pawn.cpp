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
    int          x          = currentPos.x;
    int          y          = currentPos.y;

    int direction = (_color == Color::WHITE) ? 1 : -1;
    int startRow  = (_color == Color::WHITE) ? 1 : 6;

    // Vérifier la case devant
    PositionTile frontPos  = {x, y + direction};
    ChessTile*   frontTile = board->getTile(frontPos);
    if (frontTile && !frontTile->getPiece())
    {
        moves.push_back(frontTile);

        // Vérifier si le pion peut avancer de deux cases
        if (y == startRow)
        {
            PositionTile doubleMovePos  = {x, y + 2 * direction};
            ChessTile*   doubleMoveTile = board->getTile(doubleMovePos);
            if (doubleMoveTile && !doubleMoveTile->getPiece())
            {
                moves.push_back(doubleMoveTile);
            }
        }
    }

    // Vérifier les captures diagonales
    for (int dx : {-1, 1})
    {
        PositionTile diagonalPos  = {x + dx, y + direction};
        ChessTile*   diagonalTile = board->getTile(diagonalPos);

        if (diagonalTile)
        {
            Piece* targetPiece = diagonalTile->getPiece();
            if (targetPiece && targetPiece->getColor() != _color)
            {
                moves.push_back(diagonalTile);
            }
        }
    }

    return moves;
}