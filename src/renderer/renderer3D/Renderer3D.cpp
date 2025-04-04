#include "Renderer3D.hpp"
#include <filesystem>
#include <lib/glm/ext.hpp>
#include "../../utils/errors/Exception.hpp"
#include "loader/meshLoading.hpp"
#include "scene/object/Mesh.hpp"
#include "scene/object/Object.hpp"
#include "scene/utils/Transform.hpp"
#include "shader/ShaderProgram.hpp"

Renderer3D::Renderer3D()
    : scene(), window(800, 600), shaderProgram(nullptr)
{
    glfwInit();
    window.create();
    glfwMakeContextCurrent(window.getWindow());

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    meshLoader.LoadAllMeshes();

    std::filesystem::path ressources_path = "C:/Users/colin/Desktop/IMAC/IMAC_2/S2/PROG/Chess3DProject/res";
    // Load the shaders

    shaderProgram = new ShaderProgram(
        ressources_path / "shaders" / "vertex.glsl",
        ressources_path / "shaders" / "fragment.glsl"
    );

    shaderProgram->link();

    Object object(
        Transform(),
        meshLoader.getMesh("knight"),
        shaderProgram,
        nullptr
    );

    scene.addObject(object);
};

void Renderer3D::render(ChessGame& chessGame)
{
    scene.init();
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
    if (!shaderProgram)
    {
        throw ShaderException("Shader program is not initialized in " + std::string(__FUNCTION__));
    }
    // Set the shader program to use

    // Set the view and projection matrices
    glUseProgram(shaderProgram->getId());
    shaderProgram->uniformMatrix4fv("viewMatrix", glm::value_ptr(scene.getCamera().getViewMatrix()));
    shaderProgram->uniformMatrix4fv("projectionMatrix", glm::value_ptr(scene.getCamera().getProjectionMatrix()));

    // Set the model matrix

    // Set the camera position
    shaderProgram->uniform3fv("viewPos", glm::value_ptr(scene.getCamera().getPosition()));

    // Render each object in the scene
    for (Object& obj : scene.getObjects())
    {
        shaderProgram->uniformMatrix4fv("modelMatrix", glm::value_ptr(obj.getModelMatrix()));
        renderObject(obj);
    }
}

void Renderer3D::renderObject(Object& object)
{
    glBindVertexArray(object.getMeshPtr()->getVAO());
    // Draw the model
    glDrawElements(GL_TRIANGLES, object.getMeshPtr()->getIndicesSize(), GL_UNSIGNED_SHORT, 0);
    // Unbind the VAO
    glBindVertexArray(0);
}