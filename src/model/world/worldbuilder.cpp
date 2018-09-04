#include "worldbuilder.h"

#include "poissondisksamplingpointsgenerator.h"

WorldBuilder::WorldBuilder()
{
    this->random = QRandomGenerator::global();
}

WorldBuilder* WorldBuilder::setSourcesCount(int sourcesCount)
{
    this->sourcesCount = sourcesCount;
    return this;
}

WorldBuilder *WorldBuilder::setMapDimensions(int width, int height)
{
    this->worldDimensions = new QRect(0, 0, width, height);
    return this;
}

WorldModel* WorldBuilder::build()
{
//    PoissonDiskSamplingPointsGenerator* generator = new PoissonDiskSamplingPointsGenerator(this->worldDimensions, 50, 40);
//    QVector<QVector2D*>* points = generator->generateSequence();
//    QVector<Cell*>* cells = new QVector<Cell*>();
//    for(int i = 0; i < points->size(); i++)
//    {
//        cells->append(new Cell(points->at(i)));
//    }
//    qDeleteAll(*points);
//    return new WorldModel(cells);
    QVector<Cell*>* cells = new QVector<Cell*>();
    cells->append(new Cell(new QVector2D(50, 50)));
    cells->append(new Cell(new QVector2D(150, 150)));
    cells->append(new Cell(new QVector2D(250, 250)));
    return new WorldModel(cells);
}
