#pragma once
#include <exception>
#include <string>
#include <utility>

class Exception : public std::exception {
private:
    std::string message;

public:
    Exception(std::string message)
        : message(std::move(message)) {}
    const char* what() const noexcept { return message.c_str(); }
    virtual ~Exception() = default;
};

class ShaderException : public Exception {
public:
    explicit ShaderException(std::string message)
        : Exception(std::move(message)) {}
};

class ShaderCompileException : public ShaderException {
public:
    explicit ShaderCompileException(std::string message)
        : ShaderException(std::move(message)) {}
};

// WindowException
class WindowException : public Exception {
public:
    explicit WindowException(std::string message)
        : Exception(std::move(message)) {}
};

class ShaderLinkException : public ShaderException {
public:
    explicit ShaderLinkException(std::string message)
        : ShaderException(std::move(message)) {}
};

class ShaderProgramException : public ShaderException {
public:
    explicit ShaderProgramException(std::string message)
        : ShaderException(std::move(message)) {}
};

// MeshException
class MeshException : public Exception {
public:
    explicit MeshException(std::string message)
        : Exception(std::move(message)) {}
};

// MeshLoadException
class MeshLoadException : public MeshException {
public:
    explicit MeshLoadException(std::string message)
        : MeshException(std::move(message)) {}
};

// RenderException
class RenderException : public Exception {
public:
    explicit RenderException(std::string message)
        : Exception(std::move(message)) {}
};