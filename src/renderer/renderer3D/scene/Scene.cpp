#include "Scene.hpp"

void Scene::init()
{
    for (auto& light : lights)
        light.init();
}

void Scene::addObject(Object object)
{
    objects.push_back(object);
}

void Scene::addLight(const Light& light) {}

std::vector<Object>& Scene::getObjects()
{
    return objects;
}

std::vector<Light>& Scene::getLights()
{
    return lights;
}

Camera& Scene::getCamera()
{
    return camera;
}