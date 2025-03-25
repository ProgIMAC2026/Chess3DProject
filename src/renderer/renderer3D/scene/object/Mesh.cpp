#include "Mesh.hpp"
#include <utility>

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLushort> indices)
    : vertices(std::move(vertices)), indices(std::move(indices))
{
    setupVAO();
    setupVBO();
    setupIBO();
}

GLuint Mesh::getVAO() const
{
    return VAO;
}

GLuint Mesh::getVBO() const
{
    return VBO;
}

GLuint Mesh::getIBO() const
{
    return IBO;
}

void Mesh::setupVAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    setupIBO();
    glBindVertexArray(0);
};

void Mesh::setupVBO()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(GLfloat)), vertices.data(), GL_STATIC_DRAW);
};

void Mesh::setupIBO()
{
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(GLushort)), indices.data(), GL_STATIC_DRAW);
};