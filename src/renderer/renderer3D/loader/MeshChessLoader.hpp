#pragma once

#include <filesystem>
#include <unordered_map>
#include "chessgame/piece/PieceType.hpp"
#include "renderer/renderer3D/scene/object/Mesh.hpp"

class MeshChessLoader {
    std::unordered_map<PieceType, std::filesystem::path> meshPaths{
        {PieceType::KNIGHT, "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/cavalier.obj"},
        {PieceType::BISHOP, "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/fou.obj"},
        {PieceType::ROOK, "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/tour.obj"},
        {PieceType::QUEEN, "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/reine.obj"},
        {PieceType::KING, "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/reine.obj"},
        {PieceType::PAWN, "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/tour.obj"},
        {PieceType::NONE, "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/cavalier.obj"}
    };

    std::unordered_map<PieceType, Mesh> loadedMeshes;

public:
    MeshChessLoader() = default;

    void loadChessMesh(PieceType type);
    void loadAllChessMeshes();

    Mesh* getMesh(PieceType type);
};