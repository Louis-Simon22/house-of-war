#include "gamemanager.h"
#include <QDebug>

#include "../model/geography/worldbuilder.h"

GameManager::GameManager(QObject *parent) : QObject(parent)
{
}

WorldModel* GameManager::getWorldModel()
{
    return this->gameModel ? this->gameModel->getWorldModel() : 0;
}

void GameManager::startNewGame(int width, int height, int sourcesCount)
{
    WorldBuilder* worldBuilder = new WorldBuilder();
    worldBuilder
            ->setMapDimensions(width, height)
            ->setSourcesCount(sourcesCount);
    WorldModel* worldModel = worldBuilder->build();
    this->gameModel = unique_ptr<GameModel>(new GameModel(worldModel));
}
