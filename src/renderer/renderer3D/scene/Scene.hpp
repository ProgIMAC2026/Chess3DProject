#pragma once

#include <vector>
#include "light/Light.hpp"
#include "object/Object.hpp"

class Scene {
    std::vector<Object> objects;
    std::vector<Light>  lights;

public:
    void init();
};