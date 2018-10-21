#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include <QRandomGenerator>
#include <QVector2D>

#include "../worldmodel.h"
#include <QRect>

class WorldBuilder{
public:
    WorldBuilder();

    WorldBuilder* setSourcesCount(int sourcesCount);
    WorldBuilder* setWorldDimensions(int width, int height);
    WorldModel* build() const;

    QRandomGenerator* random;
    int sourcesCount;
    QRect worldDimensions;

private:
};

#endif
