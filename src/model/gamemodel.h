#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <memory>
#include "world/worldmodel.h"
#include <QRect>

using namespace std;

class GameModel
{
public:
    GameModel(WorldModel* worldModel, QRect* worldDimensions);
    WorldModel* getWorldModel() const;
    QRect* getWorldDimensions() const;

private:
    unique_ptr<WorldModel> worldModel;
    QRect* worldDimensions;

};

#endif
