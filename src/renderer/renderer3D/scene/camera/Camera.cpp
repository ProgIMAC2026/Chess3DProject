#include "Camera.hpp"
#include <lib/glm/ext.hpp>

void Camera::updateAspectRatio(int width, int height)
{
    params.aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

TargetCamera::TargetCamera()
    : Camera({45.f, 0.1f, 100.f, 800.f / 600.f}), targetPosition(0.0f), distanceToTarget(2.0f), angleAroundVerticalAxis(0.0f), angleAroundHorizontalAxis(30.0f)
{
}

void TargetCamera::setTargetPosition(glm::vec3 targetPosition)
{
    this->targetPosition = targetPosition;
}

void TargetCamera::setDistanceToTarget(float distanceToTarget)
{
    this->distanceToTarget = distanceToTarget;
}

void TargetCamera::setAngleAroundVerticalAxis(float angle)
{
    this->angleAroundVerticalAxis = angle;
}

void TargetCamera::setAngleAroundHorizontalAxis(float angle)
{
    this->angleAroundHorizontalAxis = angle;
}

glm::vec3 TargetCamera::getPosition() const
{
    float x = targetPosition.x + distanceToTarget * cos(glm::radians(angleAroundHorizontalAxis)) * sin(glm::radians(angleAroundVerticalAxis));
    float y = targetPosition.y + distanceToTarget * sin(glm::radians(angleAroundHorizontalAxis));
    float z = targetPosition.z + distanceToTarget * cos(glm::radians(angleAroundHorizontalAxis)) * cos(glm::radians(angleAroundVerticalAxis));
    return glm::vec3(x, y, z);
}

glm::mat4 TargetCamera::getViewMatrix() const
{
    return glm::lookAt(getPosition(), targetPosition, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 TargetCamera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(params.fov), params.aspectRatio, params.nearPlane, params.farPlane);
}

void TargetCamera::rotateAroundTarget(float angle, glm::vec3 axis)
{
    if (axis == glm::vec3(0.0f, 1.0f, 0.0f)) // Vertical axis
    {
        angleAroundVerticalAxis += angle;
    }
    else if (axis == glm::vec3(1.0f, 0.0f, 0.0f)) // Horizontal axis
    {
        angleAroundHorizontalAxis += angle;
    }
}

void TargetCamera::rotate(float angle, glm::vec3 axis)
{
    rotateAroundTarget(angle, axis);
}

PointOfViewCamera::PointOfViewCamera()
    : Camera({45.f, 0.1f, 100.f, 800.f / 600.f}), position(0.0f, 1.0f, 0.0f), rotation(0.0f)
{
}

glm::vec3 PointOfViewCamera::getPosition() const
{
    return position;
}

glm::mat4 PointOfViewCamera::getViewMatrix() const
{
    glm::mat4 camera(0);
    camera = glm::rotate(camera, rotation.x, {1,0,0});
    camera = glm::rotate(camera, rotation.y, {0,1,0});
    camera = glm::rotate(camera, rotation.z, {0,0,1});

    return glm::inverse(camera);
}

glm::mat4 PointOfViewCamera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(params.fov), params.aspectRatio, params.nearPlane, params.farPlane);
}

void PointOfViewCamera::setPosition(glm::vec3 position)
{
    this->position = position;
}

void PointOfViewCamera::setRotation(glm::vec3 rotation)
{
    this->rotation = rotation;
}

void PointOfViewCamera::rotate(float angle, glm::vec3 axis)
{
    if (axis == glm::vec3(1.0f, 0.0f, 0.0f)) // X-axis
    {
        rotation.x += angle;
    }
    else if (axis == glm::vec3(0.0f, 1.0f, 0.0f)) // Y-axis
    {
        rotation.y += angle;
    }
    else if (axis == glm::vec3(0.0f, 0.0f, 1.0f)) // Z-axis
    {
        rotation.z += angle;
    }
}

