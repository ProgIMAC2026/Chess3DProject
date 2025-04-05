#pragma once

#include <utility>
#include <vector>
#include "camera/Camera.hpp"
#include "chessgame/ChessGame.hpp"
#include "light/Light.hpp"
#include "object/Object.hpp"
#include "renderer/renderer3D/loader/MeshChessLoader.hpp"
#include "renderer/renderer3D/shader/ShaderProgram.hpp"

class Scene {
    std::vector<Object> objects;
    std::vector<Light>  lights;
    Camera              camera;
    glm::mat4           modelMatrix = glm::mat4(1.0f);

public:
    Scene()
        : camera(CameraParameters{.position = glm::vec3(1.2f, 0.5f, 1.2f), .target = glm::vec3(0.f, 0.f, 0.f), .up = glm::vec3(0.f, 1.f, 0.f), .fov = 45.f, .aspect = 800.f / 600.f, .near = 0.1f, .far = 100.f}) {};

    Scene(std::vector<Object> objects, std::vector<Light> lights, Camera camera)
        : objects(std::move(objects)), lights(std::move(lights)), camera(camera) {};

    // Getters
    std::vector<Object>& getObjects();
    std::vector<Light>&  getLights();

    Camera& getCamera();

    glm::mat4 getModelMatrix() const { return modelMatrix; }

    // Setters
    void addObject(Object object);
    void addLight(const Light& light);

    // Create scene from chessgame
    static Scene createChessGameScene(ChessGame& chessGame, MeshChessLoader& meshLoader, ShaderProgram& shaderProgram);

    // Convert PositionTile to 3D position
    static glm::vec3 positionTileTo3DPosition(const PositionTile& positionTile);
};