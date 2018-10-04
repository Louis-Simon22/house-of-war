#ifndef POISSONDISKSAMPLINGPOINTSGENERATOR_H
#define POISSONDISKSAMPLINGPOINTSGENERATOR_H

#include <QVector2D>
#include <QRandomGenerator>
#include <QRect>
#include <QVector>

class PoissonDiskSamplingPointsGenerator {
public:
    PoissonDiskSamplingPointsGenerator(QRect* areaDimensions, float minimumPointDistance, long maximumGenerationAttempts);
    QVector<QVector2D *>* generateSequence();

private:
    QRect* areaDimensions;
    float minimumPointDistance;
    int maximumGenerationAttempts;
    QVector<QVector<QVector2D*>*>* backgroundGrid;
    long backgroundGridDimensionX;
    long backgroundGridDimensionY;
    QRandomGenerator* random;

    QVector<QVector<QVector2D*>*>* initializeBackgroundGrid();
    long pointToBackgroundGridYIndex(QVector2D* point);
    long pointToBackgroundGridXIndex(QVector2D* point);
    QVector2D* randomPointInAnnulus(QVector2D* point, float innerR, float outerR);
    bool pointIsFarEnoughFromOthers(long pointBackgroundGridYIndex,
                                    long pointBackgroundGridXIndex, QVector2D* point);
};

#endif // POISSONDISKSAMPLINGPOINTSGENERATOR_H
