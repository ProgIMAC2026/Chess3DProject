#pragma once

#include <lib/glm/glm.hpp>

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    Transform()
        : position(0.0f), rotation(0.0f), scale(1.0f) {}
    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : position(position), rotation(rotation), scale(scale) {}
};