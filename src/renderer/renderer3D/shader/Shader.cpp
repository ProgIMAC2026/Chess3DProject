#include "Shader.hpp"
#include <fstream>

void Shader::readShaderSource(const std::filesystem::path& filePath)
{
    std::string   line, text;
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

Shader::Shader(const std::filesystem::path& filePath, int shaderType)
    : _shaderType(shaderType)
{
    _id = glCreateShader(_shaderType);

    glShaderSource(_id, 1, &shaderSource, nullptr);

    glCompileShader(_id);
}
