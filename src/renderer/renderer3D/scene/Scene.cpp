#include "Scene.hpp"
#include <vector>
#include "chessgame/piece/Piece.hpp"
#include "utils/Transform.hpp"

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
            meshLoader.getMesh(piece->getType()),
            &shaderProgram,
            nullptr // TODO(colin): Create texture from piece
        );

        scene.addObject(object);
    }

    return scene;
}

glm::vec3 Scene::positionTileTo3DPosition(const PositionTile& positionTile)
{
    return glm::vec3(positionTile.x * 1.f / 8, 0.f, positionTile.y * 1.f / 8) - glm::vec3(0.5f, 0.f, 0.5f); // Center the board at (0, 0, 0)
}
