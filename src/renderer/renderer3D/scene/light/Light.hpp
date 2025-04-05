#pragma once

#include "renderer/renderer3D/scene/utils/Transform.hpp"
class Light {
    Transform _transform;
    glm::vec3 _color;

    float _ambientStrength  = 0.1f;
    float _diffuseStrength  = 0.5f;
    float _specularStrength = 0.5f;

    float _constantAttenuation  = 1.0f;
    float _linearAttenuation    = 0.09f;
    float _quadraticAttenuation = 0.032f;

public:
    Light(const Transform& transform, const glm::vec3& color)
        : _transform(transform), _color(color) {}

    const Transform& getTransform() const { return _transform; }
    const glm::vec3& getColor() const { return _color; }

    void setTransform(const Transform& transform) { _transform = transform; }
    void setColor(const glm::vec3& color) { _color = color; }

    glm::vec3 getAmbient() const { return _ambientStrength * _color; }
    glm::vec3 getDiffuse() const { return _diffuseStrength * _color; }
    glm::vec3 getSpecular() const { return _specularStrength * _color; }

    float getConstantAttenuation() const { return _constantAttenuation; }
    float getLinearAttenuation() const { return _linearAttenuation; }
    float getQuadraticAttenuation() const { return _quadraticAttenuation; }
};