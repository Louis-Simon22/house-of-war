#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include <memory>
#include <QVector>
#include "gamebuildstep.h"

using namespace std;

class GameBuilder
{
    public:
        explicit GameBuilder();
        void appendStep(GameBuildStep* gameBuildStep);
        void sequentiallyExecuteSteps();

    private:
        unique_ptr<QVector<unique_ptr<GameBuildStep*>>> buildSteps;
};

#endif // GAMEBUILDER_H
