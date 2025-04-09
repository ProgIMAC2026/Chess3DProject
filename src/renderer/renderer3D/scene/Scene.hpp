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
    std::vector<Object> _objects;
    std::vector<Light>  _lights;
    TargetCamera        _targetCamera;
    PointOfViewCamera   _pointOfViewCamera;
    glm::mat4           modelMatrix;

    Camera* currentCamera;


public:
    Scene()
        : _targetCamera(), _pointOfViewCamera(), modelMatrix(1.0f), currentCamera(&_targetCamera)  {};

    Scene(std::vector<Object> objects, std::vector<Light> lights)
        : _objects(std::move(objects)), _lights(std::move(lights)), _targetCamera(), _pointOfViewCamera(), modelMatrix(1.0f), currentCamera(&_targetCamera) {};


    // Getters
    std::vector<Object>& getObjects();
    std::vector<Light>&  getLights();

    TargetCamera& getTargetCamera();
    PointOfViewCamera& getPointOfViewCamera();

    Camera* getCurrentCamera() { return currentCamera; }

    void setCurrentCameraToTargetCamera() { currentCamera = &_targetCamera; }
    void setCurrentCameraToPointOfViewCamera() { currentCamera = &_pointOfViewCamera; }

    glm::mat4 getModelMatrix() const { return modelMatrix; }

    // Setters
    void addObject(Object object);
    void addLight(const Light& light);

    // Create scene from chessgame
    static Scene createChessGameScene(ChessGame& chessGame, MeshChessLoader& meshLoader, ShaderProgram& shaderProgram);

    // Convert PositionTile to 3D position
    static glm::vec3 positionTileTo3DPosition(const PositionTile& positionTile);
};