#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include "renderer/renderer3D/scene/object/Mesh.hpp"

class MeshLoader {
    const std::unordered_map<std::string, std::filesystem::path> meshPaths{
        {"knight", "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/cavalier.obj"},
        {"bishop", "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/fou.obj"},
        {"rook", "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/tour.obj"},
        {"queen", "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/reine.obj"},
        {"king", "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res/models/reine.obj"}
    };

    std::unordered_map<std::string, Mesh> loadedMeshes;

public:
    MeshLoader() = default;

    void LoadMesh(const std::string& name);
    void LoadAllMeshes();

    Mesh* getMesh(const std::string& name);
};