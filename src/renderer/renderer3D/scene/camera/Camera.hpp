#pragma once
#include <lib/glm/glm.hpp>

struct CameraParameters {
    float fov;
    float nearPlane;
    float farPlane;
    float aspectRatio;
};

class Camera {
protected:
    CameraParameters params;

public:
    explicit Camera(CameraParameters params)
        : params(params) {};

    virtual glm::vec3 getPosition() const = 0;
    virtual glm::mat4 getViewMatrix() const = 0;
    virtual glm::mat4 getProjectionMatrix() const = 0;

    void updateAspectRatio(int width, int height);

    virtual void rotate(float angle, glm::vec3 axis) = 0;
};

class TargetCamera : public Camera {
    glm::vec3 targetPosition;
    float distanceToTarget;

    float angleAroundVerticalAxis;
    float angleAroundHorizontalAxis;
public:
    explicit TargetCamera();
    explicit TargetCamera(CameraParameters params, glm::vec3 targetPosition, float distanceToTarget , float angleAroundVerticalAxis, float angleAroundHorizontalAxis )
        : Camera(params) {};

    // Setters
    void setTargetPosition(glm::vec3 targetPosition);
    void setDistanceToTarget(float distanceToTarget);
    void setAngleAroundVerticalAxis(float angle);
    void setAngleAroundHorizontalAxis(float angle);

    // Getters
    glm::vec3 getTargetPosition() const { return targetPosition; }
    float getDistanceToTarget() const { return distanceToTarget; }
    float getAngleAroundVerticalAxis() const { return angleAroundVerticalAxis; }
    float getAngleAroundHorizontalAxis() const { return angleAroundHorizontalAxis; }

    // Override
    glm::vec3 getPosition() const override;
    glm::mat4 getViewMatrix() const override;
    glm::mat4 getProjectionMatrix() const override;

    // Movement methods
    void rotate(float angle, glm::vec3 axis) override;
    void rotateAroundTarget(float angle, glm::vec3 axis);
};

class PointOfViewCamera : public Camera {

    glm::vec3 position;
    glm::vec3 rotation; // Euler angles in radians

public:
    explicit PointOfViewCamera();
    explicit PointOfViewCamera(CameraParameters params, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f))
        : Camera(params) {};


    // Override
    glm::vec3 getPosition() const override;
    glm::mat4 getViewMatrix() const override;
    glm::mat4 getProjectionMatrix() const override;

    // Movement methods
    void rotate(float angle, glm::vec3 axis) override;
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation); // Euler angles in radians
};