#include "Renderer3D.hpp"
#include <charconv>
#include <cmath>
#include <filesystem>
#include <format>
#include <iostream>
#include <lib/glm/ext.hpp>
#include <memory>
#include <string>
#include "GLFW/glfw3.h"
#include "lib/glm/fwd.hpp"
#include "loader/meshLoading.hpp"
#include "renderer/renderer3D/shader/ShaderProgram.hpp"
#include "scene/Scene.hpp"
#include "scene/light/Light.hpp"
#include "scene/object/Mesh.hpp"
#include "scene/object/Object.hpp"
#include "utils/errors/Exception.hpp"

void Renderer3D::initGlad()
{
    // Initialize GLAD to load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw -1;
    }

    // Set the viewport size
    int width  = NAN;
    int height = NAN;
    glfwGetFramebufferSize(window.getWindow(), &width, &height);
    glViewport(0, 0, width, height);
}

Renderer3D::Renderer3D()
    : scene(), window(1000, 800), shaderProgramPtr(nullptr)
{
    initGlad();

    // Set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Load the meshes
    meshLoader.loadAllMeshes();

    std::filesystem::path ressources_path = "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res";
    // Load the shaders
    shaderProgramPtr = std::make_unique<ShaderProgram>(
        ressources_path / "shaders" / "vertex.glsl",
        ressources_path / "shaders" / "fragment.glsl"
    );

    shaderProgramPtr->link();

    window.setOnKeyPress(
        [this](int key) {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                window.shouldClose(); // Close the window
                break;
            case GLFW_KEY_UP:
                scene.getCamera().move({0.0f, 0.1f, 0.0f});
                break;
            case GLFW_KEY_DOWN:
                scene.getCamera().move({0.0f, -0.1f, 0.0f});
                break;
            case GLFW_KEY_LEFT:
                scene.getCamera().rotate(-5.f, {0.0f, 1.0f, 0.0f});
                break;
            case GLFW_KEY_RIGHT:
                scene.getCamera().rotate(5.f, {0.0f, 1.0f, 0.0f});
                break;
            }
        }
    );
};

void Renderer3D::render(ChessGame& chessGame)
{
    scene = Scene::createChessGameScene(chessGame, meshLoader, *shaderProgramPtr);

    glEnable(GL_DEPTH_TEST);
    while (!window.shouldClose())
    {
        window.pollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderScene();

        window.swapBuffers();
    }
};

void Renderer3D::renderScene()
{
    if (!shaderProgramPtr)
    {
        throw ShaderException("Shader program is not initialized in " + std::string(__FUNCTION__));
    }
    // Set the shader program to use

    // Set the view and projection matrices
    glUseProgram(shaderProgramPtr->getId());

    scene.getCamera().updateProjectionMatrix(window.getWidth(), window.getHeight());

    shaderProgramPtr->uniformMatrix4fv("viewMatrix", glm::value_ptr(scene.getCamera().getViewMatrix()));
    shaderProgramPtr->uniformMatrix4fv("projectionMatrix", glm::value_ptr(scene.getCamera().getProjectionMatrix()));

    // Set Material properties
    renderMaterial();

    renderLights(scene.getLights());

    // Set the camera position
    shaderProgramPtr->uniform3fv("viewPos", glm::value_ptr(scene.getCamera().getPosition()));

    // Render each object in the scene
    for (Object& obj : scene.getObjects())
    {
        shaderProgramPtr->uniformMatrix4fv("modelMatrix", glm::value_ptr(obj.getModelMatrix()));
        renderObject(obj);
    }
}

void Renderer3D::renderObject(Object& object)
{
    if (!object.getMeshPtr())
    {
        return;
        // throw MeshException("Mesh is not initialized in " + std::string(__FUNCTION__));
    }
    glBindVertexArray(object.getMeshPtr()->getVAO());
    // Draw the model
    glDrawElements(GL_TRIANGLES, object.getMeshPtr()->getIndicesSize(), GL_UNSIGNED_SHORT, 0);
    // Unbind the VAO
    glBindVertexArray(0);
}

void Renderer3D::renderLights(std::vector<Light>& lights)
{
    // Set Light properties
    shaderProgramPtr->uniform1i("lightCount", lights.size());

    for (size_t i{0}; i < lights.size(); ++i)
    {
        const Light& light      = lights[i];
        std::string  lightIndex = std::to_string(i);

        shaderProgramPtr->uniform3fv(("lights[" + lightIndex + "].position").c_str(), glm::value_ptr(light.getTransform()._position));
        shaderProgramPtr->uniform3fv(("lights[" + lightIndex + "].ambient").c_str(), glm::value_ptr(light.getAmbient()));
        shaderProgramPtr->uniform3fv(("lights[" + lightIndex + "].diffuse").c_str(), glm::value_ptr(light.getDiffuse()));
        shaderProgramPtr->uniform3fv(("lights[" + lightIndex + "].specular").c_str(), glm::value_ptr(light.getSpecular()));
        shaderProgramPtr->uniform1f(("lights[" + lightIndex + "].constant").c_str(), light.getConstantAttenuation());
        shaderProgramPtr->uniform1f(("lights[" + lightIndex + "].linear").c_str(), light.getLinearAttenuation());
        shaderProgramPtr->uniform1f(("lights[" + lightIndex + "].quadratic").c_str(), light.getQuadraticAttenuation());
    }
}

void Renderer3D::renderMaterial()
{
    shaderProgramPtr->uniform1i("material.diffuse", 0);
    shaderProgramPtr->uniform1i("material.specular", 1);
    shaderProgramPtr->uniform1f("material.shininess", 32.0f);
}