#include "gamemodel.h"
#include <QDebug>

GameModel::GameModel(WorldModel* worldModel, QRect* worldDimensions){
    this->worldModel = unique_ptr<WorldModel>(worldModel);
    this->worldDimensions = worldDimensions;
}

WorldModel* GameModel::getWorldModel() const
{
    return this->worldModel.get();
}

QRect* GameModel::getWorldDimensions() const
{
    return this->worldDimensions;
}
