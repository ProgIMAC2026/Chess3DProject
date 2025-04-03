#include "Camera.hpp"
#include <lib/glm/ext.hpp>

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(params.position, params.target, params.up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(params.fov), params.aspect, params.near, params.far);
}

void Camera::move(glm::vec3 direction)
{
    params.position += direction;
}