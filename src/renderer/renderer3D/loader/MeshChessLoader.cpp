#include "MeshChessLoader.hpp"
#include "MeshLoading.hpp"
#include "chessgame/piece/PieceType.hpp"

void MeshChessLoader::loadChessPieceMesh(PieceType type)
{
    if (loadedPiecesMeshes.find(type) == loadedPiecesMeshes.end())
    {
        loadedPiecesMeshes[type] = loadMesh(meshPiecesPaths.at(type));
    }
}

void MeshChessLoader::loadAllChessPiecesMeshes()
{
    for (const auto& [type, path] : meshPiecesPaths)
    {
        loadChessPieceMesh(type);
    }
}

Mesh* MeshChessLoader::getPieceMesh(PieceType type)
{
    if (loadedPiecesMeshes.find(type) != loadedPiecesMeshes.end())
    {
        return &loadedPiecesMeshes[type];
    }
    return nullptr;
}

Mesh* MeshChessLoader::getBoardMesh()
{
    return &loadedBoardMesh;
}

void MeshChessLoader::loadBoardMesh()
{
    loadedBoardMesh = loadMesh(meshBoardPath);
}

void MeshChessLoader::loadAllMeshes()
{
    loadAllChessPiecesMeshes();
    loadBoardMesh();
}