#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh {
private:
    std::vector<GLfloat>  vertices;
    std::vector<GLushort> indices;

    GLuint VBO;
    GLuint VAO;
    GLuint IBO;

    static const GLuint VERTEX_ATTR_POSITION = 0;
    static const GLuint VERTEX_ATTR_NORMAL   = 1;

    void setupVAO();
    void setupVBO();
    void setupIBO();

public:
    Mesh(std::vector<GLfloat> vertices, std::vector<GLushort> indices);
    // Getter
    GLuint getVAO() const;
    GLuint getVBO() const;
    GLuint getIBO() const;
};