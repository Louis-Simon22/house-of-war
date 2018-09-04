#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include <QRandomGenerator>
#include <QVector2D>

#include "worldmodel.h"
#include "cell.h"

class WorldBuilder{
public:
    WorldBuilder();

    WorldBuilder* setSourcesCount(int sourcesCount);
    WorldBuilder* setMapDimensions(int width, int height);
    WorldModel* build();

private:
    QRandomGenerator* random;
    int sourcesCount;
    QRect* worldDimensions;
};

#endif
