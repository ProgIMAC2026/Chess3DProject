#pragma once

#include <vector>
#include "chessboard/ChessBoard.hpp"
#include "chessboard/ChessTile.hpp"
#include "chessgame/piece/Piece.hpp"
class ChessGame {
    ChessBoard _chessBoard;
    ChessTile* _selectedTile = nullptr;

public:
    ChessGame();
    ~ChessGame();
    void start();
    void update();
    void end();

    void setSelectedTile(ChessTile* tile) { _selectedTile = tile; }

    void clearSelectedTile() { _selectedTile = nullptr; }

    // Getters
    ChessBoard& getChessBoard() { return _chessBoard; }

    ChessTile* getSelectedTile() const { return _selectedTile; }
    bool       isTileSelected() const { return _selectedTile != nullptr; }

    ChessTile* getTileAtPosition(const glm::vec3& position) const;

    std::vector<Piece*> getPieces() const { return _chessBoard.getPieces(); }
};