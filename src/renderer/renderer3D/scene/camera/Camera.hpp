#pragma once
#include <lib/glm/glm.hpp>

struct CameraParameters {
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float     fov;
    float     aspect;
    float     near;
    float     far;
};

class Camera {
    CameraParameters params;

public:
    explicit Camera(CameraParameters params)
        : params(params) {};

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::vec3 getPosition() const { return params.position; }

    void move(glm::vec3 direction);

    void rotate(float angle, glm::vec3 axis);
};