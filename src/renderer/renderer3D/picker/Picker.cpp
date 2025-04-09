#include "Picker.hpp"

Picker::Picker(int width, int height)
    : _width(width), _height(height), _framebuffer(0), _pickingTexture(0), _depthTexture(0), _shaderProgramPtr(nullptr)
{
}

Picker::~Picker()
{
    glDeleteTextures(1, &_pickingTexture);
    glDeleteTextures(1, &_depthTexture);
    glDeleteFramebuffers(1, &_framebuffer);
}

void Picker::init()
{
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

    glGenTextures(1, &_pickingTexture);
    glBindTexture(GL_TEXTURE_2D, _pickingTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _pickingTexture, 0);

    glGenTextures(1, &_depthTexture);
    glBindTexture(GL_TEXTURE_2D, _depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture, 0);

    glDrawBuffers(GL_COLOR_ATTACHMENT0, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Picker::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glad_glViewport(0, 0, _width, _height);
}

void Picker::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glad_glViewport(0, 0, _width, _height);
}

void Picker::useShaderProgram() const
{
    glUseProgram(_shaderProgramPtr->getId());
}

void Picker::DisableWriting() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int Picker::getObjectIndex(int x, int y) const
{
    // Read the pixel color at the specified coordinates
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    float pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixel);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return (int)(pixel[0] * 255) - 1;
}