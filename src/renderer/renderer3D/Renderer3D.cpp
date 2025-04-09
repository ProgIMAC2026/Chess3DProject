#include "Renderer3D.hpp"
#include <cmath>
#include <filesystem>
#include <iostream>
#include <lib/glm/ext.hpp>
#include <memory>
#include <string>
#include "GLFW/glfw3.h"
#include "lib/glm/fwd.hpp"
#include "picker/Picker.hpp"
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
        throw RenderException("Failed to initialize GLAD in " + std::string(__FUNCTION__));
    }

    // Set the viewport size
    int width  = NAN;
    int height = NAN;
    glfwGetFramebufferSize(window.getWindow(), &width, &height);
    glViewport(0, 0, width, height);
}

Renderer3D::Renderer3D()
    : scene(), window(1400, 1200), shaderProgramPtr(nullptr), picker(1400, 1200), meshLoader(std::filesystem::absolute(std::filesystem::current_path() / "../..") / "res")
{
    initGlad();

    // Set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Load the meshes
    meshLoader.loadAllMeshes();

    std::filesystem::path ressources_path = std::filesystem::absolute(std::filesystem::current_path() / "../..") / "res";
    // Load the shaders
    shaderProgramPtr = std::make_unique<ShaderProgram>(
        ressources_path / "shaders" / "vertex.glsl",
        ressources_path / "shaders" / "fragment.glsl"
    );

    shaderProgramPtr->link();

    // Initialize the picker
    picker.setShaderProgram(std::make_unique<ShaderProgram>(
        ressources_path / "shaders" / "picking.vs.glsl",
        ressources_path / "shaders" / "picking.fs.glsl"
    ));

    picker.getShaderProgram().link();
    picker.init();

    window.setOnKeyPress(
        [this](int key) {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                window.shouldClose(); // Close the window
                break;
            case GLFW_KEY_UP:
                scene.getCurrentCamera()->rotate(5.f, glm::vec3(1.f, 0.f, 0.f));
                break;
            case GLFW_KEY_DOWN:
                scene.getCurrentCamera()->rotate(-5.f, glm::vec3(1.f, 0.f, 0.f));
                break;
            case GLFW_KEY_LEFT:
                scene.getCurrentCamera()->rotate(5.f, glm::vec3(0.f, 1.f, 0.f));
                break;
            case GLFW_KEY_RIGHT:
                scene.getCurrentCamera()->rotate(-5.f, glm::vec3(0.f, 1.f, 0.f));
                break;
            case GLFW_KEY_P:
                scene.setCurrentCameraToPointOfViewCamera();
                break;
            case GLFW_KEY_T:
                scene.setCurrentCameraToTargetCamera();
                break;
            }
        }
    );

    window.setOnSizeChange(
        [this](int width, int height) {
            // Update the viewport size
            glViewport(0, 0, width, height);
            Camera* camera = scene.getCurrentCamera();
            if (!camera)
            {
                throw CameraException("Camera is not initialized in " + std::string(__FUNCTION__));
            }
            camera->updateAspectRatio(width, height);
            picker.setWidth(width);
            picker.setHeight(height);
        }
    );

    window.setOnMouseClick(
        [this](int button, int action, int mods, double xpos, double ypos) {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            {
                // Get the object index at the mouse position
                int objectIndex = picker.getObjectIndex((xpos + 1) / 2 * window.getWidth(), (ypos + 1) / 2 * window.getHeight());
                if (objectIndex >= 0 && objectIndex < scene.getObjects().size())
                {
                    // Get the object from the scene using the index

                    Object& obj = scene.getObjects()[objectIndex];
                    obj.setMaterial(Material(
                        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color
                        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color
                        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color
                        32.0f                        // Shininess
                    ));
                }
            }
        }
    );
};

void Renderer3D::render(ChessGame& chessGame)
{
    scene = Scene::createChessGameScene(chessGame, meshLoader, *shaderProgramPtr);
    scene.setCurrentCameraToTargetCamera();

    glEnable(GL_DEPTH_TEST);
    while (!window.shouldClose())
    {
        window.pollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the scene
        renderScene();

        renderPickingScene();

        // Swap the buffers to display the rendered image
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

    Camera* camera = scene.getCurrentCamera();

    if (!camera)
    {
        throw CameraException("Camera is not initialized in " + std::string(__FUNCTION__));
    }

    camera->updateAspectRatio(window.getWidth(), window.getHeight());

    shaderProgramPtr->uniformMatrix4fv("viewMatrix", glm::value_ptr(camera->getViewMatrix()));
    shaderProgramPtr->uniformMatrix4fv("projectionMatrix", glm::value_ptr(camera->getProjectionMatrix()));

    renderLights(scene.getLights());

    // Set the targetCamera position
    shaderProgramPtr->uniform3fv("viewPos", glm::value_ptr(camera->getPosition()));

    // Render each object in the scene
    for (Object& obj : scene.getObjects())
    {
        // Set Material properties
        renderMaterial(obj.getMaterial());

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

void Renderer3D::renderMaterial(Material& material)
{
    shaderProgramPtr->uniform3fv("material.ambient", glm::value_ptr(material.getAmbient()));
    shaderProgramPtr->uniform3fv("material.diffuse", glm::value_ptr(material.getDiffuse()));
    shaderProgramPtr->uniform3fv("material.specular", glm::value_ptr(material.getSpecular()));
    shaderProgramPtr->uniform1f("material.shininess", material.getShininess());
}

void Renderer3D::renderPickingScene()
{
    // Render the picker
    picker.bind();
    picker.useShaderProgram();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    picker.getShaderProgram().uniformMatrix4fv("viewMatrix", glm::value_ptr(scene.getCurrentCamera()->getViewMatrix()));
    picker.getShaderProgram().uniformMatrix4fv("projectionMatrix", glm::value_ptr(scene.getCurrentCamera()->getProjectionMatrix()));

    for (size_t i{0}; i < scene.getObjects().size(); ++i)
    {
        Object& obj = scene.getObjects()[i];
        // Set Material properties
        picker.getShaderProgram().uniformMatrix4fv("modelMatrix", glm::value_ptr(obj.getModelMatrix()));
        picker.getShaderProgram().uniform1f("gObjectIndex", (i + 1) / 255.0f);
        renderObject(obj);
    }

    picker.unbind();
}