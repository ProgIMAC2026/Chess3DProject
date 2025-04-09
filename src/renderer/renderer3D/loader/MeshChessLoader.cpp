#include "MeshChessLoader.hpp"
#include "MeshLoading.hpp"
#include "chessgame/piece/PieceType.hpp"

MeshChessLoader::MeshChessLoader(std::filesystem::path ressourcePath) : ressourcePath(ressourcePath){}

void MeshChessLoader::loadChessPieceMesh(PieceType type)
{
    if (loadedPiecesMeshes.find(type) == loadedPiecesMeshes.end())
    {
        loadedPiecesMeshes[type] = loadMesh(ressourcePath / meshPiecesPaths.at(type));
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
    loadedBoardMesh = loadMesh(ressourcePath / meshBoardPath);
}

void MeshChessLoader::loadAllMeshes()
{
    loadAllChessPiecesMeshes();
    loadBoardMesh();
}