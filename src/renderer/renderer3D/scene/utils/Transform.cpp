#include "Transform.hpp"
#include <lib/glm/ext.hpp>

glm::mat4 Transform::getModelMatrix() const
{
    glm::mat4 model{1.0f};
    model = glm::translate(model, _position);
    model = glm::rotate(model, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, _scale);
    return model;
}