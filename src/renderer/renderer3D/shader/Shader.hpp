#pragma once

#include <glad/glad.h>
#include <filesystem>

class Shader {
    GLuint        _id;
    const GLchar* shaderSource;
    int           _shaderType;

    void readShaderSource(const std::filesystem::path& filePath);

public:
    Shader(const std::filesystem::path& filePath, int shaderType);

    void compileShader();

    GLuint getId() const { return _id; }
};