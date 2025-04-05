#include "MeshChessLoader.hpp"
#include "MeshLoading.hpp"
#include "chessgame/piece/PieceType.hpp"

void MeshChessLoader::loadChessMesh(PieceType type)
{
    if (loadedMeshes.find(type) == loadedMeshes.end())
    {
        loadedMeshes[type] = loadMesh(meshPaths.at(type));
    }
}

void MeshChessLoader::loadAllChessMeshes()
{
    for (const auto& [type, path] : meshPaths)
    {
        loadChessMesh(type);
    }
}

Mesh* MeshChessLoader::getMesh(PieceType type)
{
    if (loadedMeshes.find(type) != loadedMeshes.end())
    {
        return &loadedMeshes[type];
    }
    return nullptr;
}