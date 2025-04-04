#include "ShaderProgram.hpp"
#include "../../../utils/errors/Exception.hpp"

ShaderProgram::ShaderProgram(
    std::filesystem::path vertexShaderPath,
    std::filesystem::path fragmentShaderPath
)
    : _id(glCreateProgram()), _vertexShader(vertexShaderPath, GL_VERTEX_SHADER), _fragmentShader(fragmentShaderPath, GL_FRAGMENT_SHADER)
{
    if (_id == 0)
        throw ShaderException("Error creating shader program in " + std::string(__FUNCTION__));

    glAttachShader(_id, _vertexShader.getId());
    glAttachShader(_id, _fragmentShader.getId());
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_id);
}

void ShaderProgram::link()
{
    glLinkProgram(_id);

    // Check for linking errors
    GLint status;
    glGetProgramiv(_id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        throw ShaderException("Error linking shader program in " + std::string(__FUNCTION__));
    }
}

void ShaderProgram::uniformMatrix4fv(const char* name, const GLfloat* value)
{
    GLint location = glGetUniformLocation(_id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void ShaderProgram::uniform3fv(const char* name, const GLfloat* value)
{
    GLint location = glGetUniformLocation(_id, name);
    glUniform3fv(location, 1, value);
}

void ShaderProgram::uniform1f(const char* name, const GLfloat value)
{
    GLint location = glGetUniformLocation(_id, name);
    glUniform1f(location, value);
}

void ShaderProgram::uniform1i(const char* name, const GLint value)
{
    GLint location = glGetUniformLocation(_id, name);
    glUniform1i(location, value);
}
