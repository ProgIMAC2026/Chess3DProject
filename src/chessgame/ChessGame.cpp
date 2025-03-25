#include "ChessGame.hpp"
#include "piece/Bishop.hpp"
#include "piece/King.hpp"
#include "piece/Knight.hpp"
#include "piece/Pawn.hpp"
#include "piece/Queen.hpp"
#include "piece/Rook.hpp"

ChessGame::ChessGame()
    : _chessBoard()
{
    // Create pieces
    _chessBoard.createPiece<Rook>(Color::BLACK, _chessBoard.getTile({7, 0}));
    _chessBoard.createPiece<Rook>(Color::BLACK, _chessBoard.getTile({7, 7}));
    _chessBoard.createPiece<Rook>(Color::WHITE, _chessBoard.getTile({0, 0}));
    _chessBoard.createPiece<Rook>(Color::WHITE, _chessBoard.getTile({0, 7}));

    _chessBoard.createPiece<Knight>(Color::BLACK, _chessBoard.getTile({7, 1}));
    _chessBoard.createPiece<Knight>(Color::BLACK, _chessBoard.getTile({7, 6}));
    _chessBoard.createPiece<Knight>(Color::WHITE, _chessBoard.getTile({0, 1}));
    _chessBoard.createPiece<Knight>(Color::WHITE, _chessBoard.getTile({0, 6}));

    _chessBoard.createPiece<Bishop>(Color::BLACK, _chessBoard.getTile({7, 2}));
    _chessBoard.createPiece<Bishop>(Color::BLACK, _chessBoard.getTile({7, 5}));
    _chessBoard.createPiece<Bishop>(Color::WHITE, _chessBoard.getTile({0, 2}));
    _chessBoard.createPiece<Bishop>(Color::WHITE, _chessBoard.getTile({0, 5}));

    _chessBoard.createPiece<King>(Color::BLACK, _chessBoard.getTile({7, 4}));
    _chessBoard.createPiece<King>(Color::WHITE, _chessBoard.getTile({0, 4}));

    _chessBoard.createPiece<Queen>(Color::BLACK, _chessBoard.getTile({7, 3}));
    _chessBoard.createPiece<Queen>(Color::WHITE, _chessBoard.getTile({0, 3}));

    for (int i = 0; i < 8; i++)
    {
        _chessBoard.createPiece<Pawn>(Color::BLACK, _chessBoard.getTile({6, i}));
        _chessBoard.createPiece<Pawn>(Color::WHITE, _chessBoard.getTile({1, i}));
    }

    // Set selected tile
    _selectedTile = _chessBoard.getTile({2, 2});
}

ChessGame::~ChessGame() {};

void ChessGame::start() {}

void ChessGame::update() {}

void ChessGame::end() {}