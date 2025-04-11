#include "Scene.hpp"
#include <iostream>
#include <vector>
#include "chessgame/piece/Color.hpp"
#include "chessgame/piece/Piece.hpp"
#include "chessgame/piece/PieceType.hpp"
#include "light/Light.hpp"
#include "material/Material.hpp"
#include "object/Object.hpp"
#include "object/PieceObject.hpp"
#include "object/TileObject.hpp"
#include "utils/Transform.hpp"

void Scene::addObject(Object* object)
{
    _objects.push_back(object);
}

void Scene::addLight(const Light& light)
{
    _lights.push_back(light);
}

std::vector<Object*>& Scene::getObjects()
{
    return _objects;
}

std::vector<Light>& Scene::getLights()
{
    return _lights;
}

TargetCamera& Scene::getTargetCamera()
{
    return _targetCamera;
}

PointOfViewCamera& Scene::getPointOfViewCamera()
{
    return _pointOfViewCamera;
}

Scene Scene::createChessGameScene(ChessGame& chessGame, MeshChessLoader& meshLoader, ShaderProgram& shaderProgram)
{
    std::vector<Piece*> pieces = chessGame.getChessBoard().getPieces();
    Scene               scene;
    for (Piece* piece : pieces)
    {
        // Create object from piece
        Object* object = new PieceObject(
            Transform(
                positionTileTo3DPosition(piece->getPosition()),
                glm::vec3(0.f, 180.f, 0.f) * (piece->getColor() == Color::BLACK ? 0.f : 1.f), // Rotate the piece to face the camera
                glm::vec3(1.f)
            ),
            meshLoader.getPieceMesh(piece->getType()),
            &shaderProgram,
            Material(
                piece->getColor() == Color::BLACK ? glm::vec3(1.f, 1.f, 1.f) : glm::vec3(0.f, 0.f, 0.f),
                piece->getColor() == Color::BLACK ? glm::vec3(1.f, 1.f, 1.f) : glm::vec3(0.2f),
                piece->getColor() == Color::BLACK ? glm::vec3(1.f, 1.f, 1.f) : glm::vec3(0.2f),
                32.f
            ),
            piece
        );

        scene.addObject(object);
    }

    // Create object from board
    Object* boardObject = new Object(
        Transform(
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(.5f)
        ),
        meshLoader.getBoardMesh(),
        &shaderProgram,
        Material(
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(1.f),
            glm::vec3(1.f),
            10.f
        )
    );

    scene.addObject(boardObject);

    createChessBoard(meshLoader, shaderProgram, scene, chessGame);

    Light light1(
        Transform(
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
        ),
        glm::vec3(1.f, 1.f, 1.f)
    );

    Light light2(
        Transform(
            glm::vec3(-1.f, 1.f, -1.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
        ),
        glm::vec3(1.f, 1.f, 1.f)
    );

    scene.addLight(light1);
    scene.addLight(light2);

    return scene;
}

void Scene::createChessBoard(MeshChessLoader& meshLoader, ShaderProgram& shaderProgram, Scene& scene, ChessGame& chessgame)
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            // Create object from board tile
            Object* object = new TileObject(
                Transform(
                    glm::vec3(i, 0.f, j) / 8.f - glm::vec3(1.f, 0.f, 1.f) * (0.5f - 1.f / 16), // Center the board at (0, 0, 0)
                    glm::vec3(0.f),
                    glm::vec3(1.f)
                ),
                meshLoader.getBoardTileMesh(),
                &shaderProgram,
                Material(
                    (i + j) % 2 == 0 ? glm::vec3(1.f, 1.f, 1.f) : glm::vec3(0.f, 0.f, 0.f),
                    glm::vec3(0.4f),
                    glm::vec3(2.f),
                    5.f
                ),
                chessgame.getTileAtPosition({i, j})
            );
            scene.addObject(object);
        }
    }
}

glm::vec3 Scene::positionTileTo3DPosition(const PositionTile& positionTile)
{
    return (glm::vec3(positionTile.x, 0.f, positionTile.y)) / 8.f - glm::vec3(1.f, 0.f, 1.f) * (0.5f - 1.f / 16); // Center the board at (0, 0, 0)
}
