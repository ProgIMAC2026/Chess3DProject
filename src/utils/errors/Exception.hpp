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
