#include "Scene.hpp"

void Scene::init()
{
    for (auto& object : objects)
        object.init();
    for (auto& light : lights)
        light.init();
}