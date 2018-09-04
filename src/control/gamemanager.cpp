#include "gamemanager.h"
#include <QDebug>

GameManager::GameManager(QObject *parent) : QObject(parent)
{
}

void GameManager::prepareNewGame(int width, int height, int sourcesCount)
{
    this->worldBuilder = unique_ptr<WorldBuilder>(new WorldBuilder());
    this->worldBuilder
            ->setMapDimensions(width, height)
            ->setSourcesCount(sourcesCount);
    this->shouldCreateNewGame = true;
}

void GameManager::instantiateWorld()
{
    if (this->shouldCreateNewGame)
    {
        WorldModel* worldModel = this->worldBuilder->build();
        this->gameModelPtr = unique_ptr<GameModel>(new GameModel(worldModel));
        this->shouldCreateNewGame = false;
    }
    else
    {
        qDebug() << "Should not create new game??";
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
