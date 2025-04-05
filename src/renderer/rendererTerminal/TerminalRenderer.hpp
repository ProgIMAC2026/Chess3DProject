#pragma once

#include "../Renderer.hpp"

class TerminalRenderer : public Renderer {
public:
    char getPieceSymbol(PieceType type, Color color) const;
    void render(ChessGame& chessGame) override;
};