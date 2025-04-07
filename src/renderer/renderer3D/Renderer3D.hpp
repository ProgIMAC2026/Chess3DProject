#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <memory>
#include "../Renderer.hpp"
#include "loader/MeshChessLoader.hpp"
#include "scene/Scene.hpp"
#include "shader/ShaderProgram.hpp"
#include "window/Window.hpp"

class Renderer3D : public Renderer {
private:
    Scene  scene;
    Window window;

    std::unique_ptr<ShaderProgram> shaderProgramPtr;
    MeshChessLoader                meshLoader;

    // Initializes the OpenGL context and sets up the viewport
    void initGlad();

public:
    Renderer3D();

    void render(ChessGame& chessGame) override;

    void renderScene();
    void renderObject(Object& object);

    void renderLights(std::vector<Light>& lights);
    void renderMaterial(Material& material);
};