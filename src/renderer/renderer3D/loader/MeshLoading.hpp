#pragma once

#include <filesystem>
#include "renderer/renderer3D/scene/object/Mesh.hpp"

// Load a mesh from a file
Mesh loadMesh(const std::filesystem::path& filepath);