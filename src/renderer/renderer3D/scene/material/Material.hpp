#pragma once

#include <lib/glm/glm.hpp>
class Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float     shininess;

public:
    Material(const glm::vec3& ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

    // Getters
    const glm::vec3& getAmbient() const { return ambient; }
    const glm::vec3& getDiffuse() const { return diffuse; }
    const glm::vec3& getSpecular() const { return specular; }
    float            getShininess() const { return shininess; }
};
