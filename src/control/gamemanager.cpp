#include "gamemanager.h"
#include <QDebug>

GameManager::GameManager(QObject *parent) : QObject(parent)
{
}

void GameManager::prepareNewGame(int width, int height, int sourcesCount)
{
    this->worldBuilder = unique_ptr<WorldBuilder>(new WorldBuilder());
    this->worldBuilder
            ->setWorldDimensions(width, height)
            ->setSourcesCount(sourcesCount);
    this->shouldCreateNewWorld = true;
}

void GameManager::instantiateWorld()
{
    if (this->shouldCreateNewWorld)
    {
        WorldModel* worldModel = this->worldBuilder->build();
        this->gameModelPtr = unique_ptr<GameModel>(new GameModel(worldModel, this->worldBuilder->worldDimensions));
        this->shouldCreateNewWorld = false;
    }
    else
    {
        // TODO implement loading world
        qDebug() << "Should not create new world";
    }
}

GameModel* GameManager::getGameModel() const
{
    return this->gameModelPtr.get();
}

WorldModel* GameManager::getWorldModel() const
{
    return this->gameModelPtr->getWorldModel();
}

QRect GameManager::getWorldDimensions() const
{
    QRect worldDimensions = *this->gameModelPtr->getWorldDimensions();
    return worldDimensions;
}
