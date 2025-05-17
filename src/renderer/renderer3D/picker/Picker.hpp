#pragma once

#include <glad/glad.h>
#include <memory>
#include "renderer/renderer3D/shader/ShaderProgram.hpp"

class Picker {
    int _width;
    int _height;

    unsigned int _framebuffer;
    GLuint       _pickingTexture;
    GLuint       _depthTexture;

    std::unique_ptr<ShaderProgram> _shaderProgramPtr;

public:
    Picker(int width, int heigh);
    ~Picker();

    // Initialize the framebuffer and textures
    void init();

    // Setters
    void setWidth(int width) { _width = width; }
    void setHeight(int height) { _height = height; }

    ShaderProgram& getShaderProgram() { return *_shaderProgramPtr; }
    void           setShaderProgram(std::unique_ptr<ShaderProgram> shaderProgramPtr)
    {
        _shaderProgramPtr = std::move(shaderProgramPtr);
    }

    // Bind the framebuffer for rendering
    void bind() const;
    void unbind() const;
    void useShaderProgram() const;

    // Writing functions
    void EnableWriting() const;
    void DisableWriting() const;

    int getObjectIndex(int x, int y) const;
};