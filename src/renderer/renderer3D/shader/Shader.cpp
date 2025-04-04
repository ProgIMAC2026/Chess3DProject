#include "Shader.hpp"
#include <fstream>
#include "../../../utils/errors/Exception.hpp"

Shader::Shader(const std::filesystem::path& filePath, int shaderType)
    : _shaderType(shaderType), shaderSource(nullptr), _id(glCreateShader(shaderType))
{
    readShaderSource(filePath);

    glShaderSource(_id, 1, &shaderSource, nullptr);

    compileShader();
}

void Shader::readShaderSource(const std::filesystem::path& filePath)
{
    std::string   line;
    std::string   text;
    std::ifstream in(filePath);
    if (!in.is_open())
        throw -1;
    if (!in.good())
        throw -1;

    while (std::getline(in, line))
    {
        text += line + "\n";
    }

    auto* shaderSourceFile = new std::string{text};
    shaderSource           = shaderSourceFile->c_str();
}

void Shader::compileShader()
{
    glCompileShader(_id);

    // Check for compilation errors
    GLint status;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        int length{0};
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = new char[length];
        glGetShaderInfoLog(_id, length, nullptr, infoLog);
        throw ShaderException{"Error compiling shader: " + std::string{infoLog}};
    }
}
