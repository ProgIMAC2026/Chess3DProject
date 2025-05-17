#pragma once
#include <glad/glad.h>
#include "Shader.hpp"

class ShaderProgram {
    GLuint _id;
    Shader _vertexShader;
    Shader _fragmentShader;

public:
    // Constructor and destructor
    ShaderProgram() = delete;
    ShaderProgram(
        std::filesystem::path vertexShaderPath,
        std::filesystem::path fragmentShaderPath
    );

    ~ShaderProgram();

    // Getters
    GLuint getId() const { return _id; }

    void link();

    // Uniform functions
    void uniformMatrix4fv(const char* name, const GLfloat* value);
    void uniform3fv(const char* name, const GLfloat* value);
    void uniform1f(const char* name, const GLfloat value);
    void uniform1i(const char* name, const GLint value);
};