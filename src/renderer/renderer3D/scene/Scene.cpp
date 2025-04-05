#include "Scene.hpp"
#include <vector>
#include "chessgame/piece/Piece.hpp"
#include "light/Light.hpp"
#include "utils/Transform.hpp"

void Scene::addObject(Object object)
{
    objects.push_back(object);
}

void Scene::addLight(const Light& light)
{
    lights.push_back(light);
}

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

Scene Scene::createChessGameScene(ChessGame& chessGame, MeshChessLoader& meshLoader, ShaderProgram& shaderProgram)
{
    std::vector<Piece*> pieces = chessGame.getChessBoard().getPieces();
    Scene               scene;
    for (Piece* piece : pieces)
    {
        // Create object from piece
        Object object(
            Transform(
                positionTileTo3DPosition(piece->getPosition()),
                glm::vec3(0.f),
                glm::vec3(1.f)
            ),
            meshLoader.getPieceMesh(piece->getType()),
            &shaderProgram,
            nullptr // TODO(colin): Create texture from piece
        );

        scene.addObject(object);
    }

    // Create object from board
    Object boardObject(
        Transform(
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(.5f)
        ),
        meshLoader.getBoardMesh(),
        &shaderProgram,
        nullptr // TODO(colin): Create texture from board
    );

    scene.addObject(boardObject);

    Light light1(
        Transform(
            glm::vec3(-1.f, 1.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
        ),
        glm::vec3(0.f, 0.2f, 0.f)
    );

    Light light2(
        Transform(
            glm::vec3(1.f, 1.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
        ),
        glm::vec3(1.f, 1.f, 1.f)
    );

    scene.addLight(light1);
    scene.addLight(light2);

    return scene;
}

glm::vec3 Scene::positionTileTo3DPosition(const PositionTile& positionTile)
{
    return (glm::vec3(positionTile.x, 0.f, positionTile.y) + glm::vec3(0.5f, 0.f, 0.5f)) / 8.f - glm::vec3(0.5f, 0.f, 0.5f); // Center the board at (0, 0, 0)
}
