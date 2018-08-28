#include "gamemodel.h"
#include <QDebug>

GameModel::GameModel(WorldModel* worldModel){
    this->worldModel = unique_ptr<WorldModel>(worldModel);
}

WorldModel* GameModel::getWorldModel()
{
    return this->worldModel.get();
}
