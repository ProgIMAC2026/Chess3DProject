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

void Camera::rotate(float angle, glm::vec3 axis)
{
    params.position = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * glm::vec4(params.position, 1.0f);
    params.target   = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * glm::vec4(params.target, 1.0f);
}

void Camera::updateProjectionMatrix(int width, int height)
{
    params.aspect = (float)width / (float)height;
}