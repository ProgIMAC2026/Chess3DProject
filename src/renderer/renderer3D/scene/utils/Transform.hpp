#pragma once

#include <lib/glm/ext.hpp>

struct Transform {
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
    Transform()
        : _position(0.0f), _rotation(0.0f), _scale(1.0f) {}
    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : _position(position), _rotation(rotation), _scale(scale) {}

    void move(const glm::vec3& delta)
    {
        _position += delta;
    }

    void rotate(const glm::vec3& delta)
    {
        _rotation += delta;
    }

    void scale(const glm::vec3& factor)
    {
        _scale *= factor;
    }

    glm::mat4 getModelMatrix() const;
};