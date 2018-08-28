#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <memory>
#include "geography/worldmodel.h"

using namespace std;

class GameModel
{
public:
    GameModel(WorldModel* worldModel);
    WorldModel* getWorldModel();

private:
    unique_ptr<WorldModel> worldModel;

};

#endif
