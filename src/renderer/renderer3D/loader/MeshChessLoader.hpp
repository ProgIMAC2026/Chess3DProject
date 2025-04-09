#pragma once

#include <filesystem>
#include <unordered_map>
#include "chessgame/piece/PieceType.hpp"
#include "renderer/renderer3D/scene/object/Mesh.hpp"

class MeshChessLoader {

    std::filesystem::path ressourcePath;

    std::unordered_map<PieceType, std::filesystem::path> meshPiecesPaths{
        {PieceType::KNIGHT, "models/cavalier.obj"},
        {PieceType::BISHOP, "models/fou.obj"},
        {PieceType::ROOK, "models/tour.obj"},
        {PieceType::QUEEN, "models/reine.obj"},
        {PieceType::KING, "models/reine.obj"},
        {PieceType::PAWN, "models/pion.obj"},
        {PieceType::NONE, "models/pion.obj"}
    };

    std::filesystem::path meshBoardPath = "models/fond_plateau.obj";
    std::filesystem::path meshBoardTilePath = "models/case.obj";

    std::unordered_map<PieceType, Mesh> loadedPiecesMeshes;
    Mesh                                loadedBoardMesh;
    Mesh                                loadedBoardTileMesh;

public:
    MeshChessLoader(std::filesystem::path ressourcePath);

    void loadChessPieceMesh(PieceType type);
    void loadAllChessPiecesMeshes();

    Mesh* getPieceMesh(PieceType type);

    Mesh* getBoardMesh();
    void  loadBoardMesh();

    Mesh* getBoardTileMesh();
    void  loadBoardTileMesh();

    void loadAllMeshes();
};