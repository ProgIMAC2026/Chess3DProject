#include "Renderer2D.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>
#include "chessgame/chessboard/ChessBoard.hpp"
#include "chessgame/chessboard/ChessTile.hpp"
#include "chessgame/piece/Color.hpp"
#include "chessgame/piece/Piece.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "renderer/renderer3D/window/Window.hpp"

Renderer2D::Renderer2D()
{
}

Renderer2D::~Renderer2D()
{
    // Cleanup ImGui context
    ImGui::DestroyContext();
}

void Renderer2D::render(ChessGame& chessGame)
{
    float       value{0.f};
    ChessBoard& board = chessGame.getChessBoard();

    quick_imgui::loop(
        "Chess",
        {
            .init = [&]() {
                // Setup ImGui context
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                (void)io;
                ImGui::StyleColorsDark(); // Setup style;

                io.Fonts->AddFontDefault();
                io.Fonts->AddFontFromFileTTF("C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/fonts/MVALFONT.TTF", 32.0f); },
            .loop = [&]() {
                    ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

                    ImGui::Begin("ChessGame");

                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

                    ImGuiIO& io = ImGui::GetIO();
                    ImGui::PushFont(io.Fonts->Fonts[1]);

                    ChessTile* tile = chessGame.getSelectedTile();
                    std::vector<ChessTile*> possibleMoves {};
                    if (tile != nullptr)
                    {
                        if(tile->getPiece() != nullptr)
                            possibleMoves = tile->getPiece()->getPossibleMoves();
                    }

                    for (size_t x{0}; x < 8; ++x)
                    {
                        for (size_t y{0}; y < 8; ++y)
                        {

                            // Color
                            renderTile(
                                board.getTile({x, y}),
                                chessGame.isPossibleMove(board.getTile({x, y})),
                                chessGame.isTileSelected(board.getTile({x, y})),
                                [&]() {
                                    ChessTile* currentTile = board.getTile({x, y});
                                    if (currentTile == nullptr)
                                        return;
                                    if (chessGame.isTileSelected(currentTile))
                                    {
                                        chessGame.clearSelectedTile();
                                        return;
                                    }
                                    ChessTile* selectedTile = chessGame.getSelectedTile();
                                    if (selectedTile == nullptr)
                                    {
                                        if(currentTile->getPiece() == nullptr)
                                            return;
                                        if (currentTile->getPiece()->getColor() != chessGame.getCurrentTurn())
                                            return;
                                        chessGame.setSelectedTile(currentTile);
                                        return;
                                    }
                                    if (selectedTile == currentTile)
                                        return;
                                    Piece* selectedPiece = selectedTile->getPiece();
                                    if (selectedPiece == nullptr)
                                        return;
                                    if (selectedPiece->getColor() != chessGame.getCurrentTurn())
                                        return;

                                    if (chessGame.isPossibleMove(currentTile))
                                    {
                                        chessGame.movePieceTo(selectedPiece, currentTile);
                                        chessGame.clearSelectedTile();
                                        return;
                                    }
                                    
                                }
                            );
                            ImGui::SameLine();
                        }
                        ImGui::NewLine();
                    }
                    ImGui::PopFont();
                    ImGui::PopStyleVar(2);
                    ImGui::End(); },
        }
    );
}

void Renderer2D::renderTile(const ChessTile* tile, bool isPossibleMove, bool isSelected, std::function<void()> onClick)
{
    if (tile->getPosition().x % 2 == 0 && tile->getPosition().y % 2 == 1 || tile->getPosition().x % 2 == 1 && tile->getPosition().y % 2 == 0)
    {
        if (isPossibleMove)
            ImGui::PushStyleColor(ImGuiCol_Button, params.TileSelectableColor1);
        else
            ImGui::PushStyleColor(ImGuiCol_Button, params.TileColor1);
    }
    else
    {
        if (isPossibleMove)
            ImGui::PushStyleColor(ImGuiCol_Button, params.TileSelectableColor2);
        else
            ImGui::PushStyleColor(ImGuiCol_Button, params.TileColor2);
    }

    if (tile->getPiece() != nullptr)
        if (isSelected)
            ImGui::PushStyleColor(ImGuiCol_Text, params.TileSelectedColor);
        else if (tile->getPiece()->getColor() == Color::WHITE)
            ImGui::PushStyleColor(ImGuiCol_Text, params.PieceColor2);
        else if (tile->getPiece()->getColor() == Color::BLACK)
            ImGui::PushStyleColor(ImGuiCol_Text, params.PieceColor1);
        else
            ImGui::PushStyleColor(ImGuiCol_Text, params.PieceColor2);
    else
        ImGui::PushStyleColor(ImGuiCol_Text, params.PieceColor2);

    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, params.TileHoveredColor);
    ImGui::PushID(tile->getPosition().x + tile->getPosition().y * 8);

    if (ImGui::Button(getLabel(tile).c_str(), {100.0, 100.0}))
    {
        if (onClick)
            onClick();
        else
            std::cout << "Button clicked!" << std::endl;
    }
    ImGui::PopID();
    ImGui::PopStyleColor(3);
}

std::string Renderer2D::getLabel(const ChessTile* tile)
{
    if (tile->getPiece() != nullptr)
    {
        switch (tile->getPiece()->getType())
        {
        case PieceType::PAWN:
            return "p";
        case PieceType::ROOK:
            return "r";
        case PieceType::KNIGHT:
            return "n";
        case PieceType::BISHOP:
            return "b";
        case PieceType::QUEEN:
            return "q";
        case PieceType::KING:
            return "k";
        default:
            return " ";
        }
    }
    return " ";
}