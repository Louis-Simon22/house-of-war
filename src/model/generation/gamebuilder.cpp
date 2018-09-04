#include "gamebuilder.h"

GameBuilder::GameBuilder()
{
    QVector<unique_ptr<GameBuildStep*>>* buildStepsList = new QVector<unique_ptr<GameBuildStep*>>();
    this->buildSteps = unique_ptr<QVector<unique_ptr<GameBuildStep*>>>(buildStepsList);
}

void GameBuilder::appendStep(GameBuildStep* gameBuildStep)
{
//    this->buildSteps->append(unique_ptr<GameBuildStep*>(gameBuildStep));
}

void GameBuilder::sequentiallyExecuteSteps()
{
    for (int i = 0; i < this->buildSteps->size(); i++)
    {
        (*this->buildSteps->at(i))->build();
    }
}
