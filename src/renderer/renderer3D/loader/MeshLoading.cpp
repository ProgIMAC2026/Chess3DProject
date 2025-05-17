#include "MeshLoading.hpp"
#include <tiny_obj_loader.h>
#include "utils/errors/Exception.hpp"

Mesh loadMesh(const std::filesystem::path& filepath)
{
    std::vector<GLfloat>  vertices;
    std::vector<GLushort> indices;

    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;
    std::string                      warn;
    std::string                      err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.generic_string().c_str(), nullptr, true))
    {
        throw MeshLoadException("Failed to load mesh: " + err);
    }

    // Loop over shapes
    for (auto& shape : shapes)
    {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t i = 0; i < shape.mesh.indices.size(); i++)
        {
            tinyobj::index_t index = shape.mesh.indices[i];
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            if (!attrib.normals.empty())
            {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else
            {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
            indices.push_back(i);
        }
    }
    return {vertices, indices};
}