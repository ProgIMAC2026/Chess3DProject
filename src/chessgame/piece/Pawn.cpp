#include "Pawn.hpp"
#include "chessgame/chessboard/ChessBoard.hpp"

std::vector<ChessTile*> Pawn::getPossibleMoves()
{
    ChessBoard*             board = _currentTilePtr->getBoard();
    std::vector<ChessTile*> moves;

    int direction = _color == Color::WHITE ? 1 : -1;
    moves.push_back(board->getTile({getPosition().x + direction, getPosition().y}));
    moves.push_back(board->getTile({getPosition().x + direction * 2, getPosition().y}));

    return moves;
}