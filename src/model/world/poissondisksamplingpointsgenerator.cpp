#include "poissondisksamplingpointsgenerator.h"

#include <QtMath>
#include "../../utils/utils.h"

using namespace utils;

PoissonDiskSamplingPointsGenerator::PoissonDiskSamplingPointsGenerator(QRect* areaDimensions, float minimumPointDistance, long maximumGenerationAttempts)
{
    this->areaDimensions = areaDimensions;
    this->minimumPointDistance = minimumPointDistance;
    this->maximumGenerationAttempts = maximumGenerationAttempts;
    this->random = QRandomGenerator::global();
}

QVector<QVector2D *>* PoissonDiskSamplingPointsGenerator::generateSequence()
{
    this->backgroundGrid = this->initializeBackgroundGrid();

    QVector2D* initialPoint = new QVector2D(randomBoundedFloat(this->random, (float) this->areaDimensions->left(), (float) this->areaDimensions->right()),
                                            randomBoundedFloat(this->random, (float) this->areaDimensions->top(), (float) this->areaDimensions->bottom()));
    // TODO initialize the lists with an approximate size
    QVector<QVector2D*>* generatedPoints = new QVector<QVector2D*>();
    QVector<QVector2D*>* activeList = new QVector<QVector2D*>();
    generatedPoints->append(initialPoint);
    activeList->append(initialPoint);

    this->backgroundGrid->at(this->pointToBackgroundGridYIndex(initialPoint))
            ->insert(this->pointToBackgroundGridXIndex(initialPoint), initialPoint);
    int limit = 0;
    while (!activeList->isEmpty() && limit++ < 100)
    {
        long randomActiveListIndex = this->random->bounded(0, activeList->size());
        bool isPointValid = false;
        for (long i = 0; i < this->maximumGenerationAttempts && !isPointValid; i++)
        {
            QVector2D* randomPointInAnnulus = this->randomPointInAnnulus(activeList->at(randomActiveListIndex),
                                                                         minimumPointDistance, minimumPointDistance * 2.0f);
            long pointBackgroundGridYIndex = this->pointToBackgroundGridYIndex(randomPointInAnnulus);
            long pointBackgroundGridXIndex = this->pointToBackgroundGridXIndex(randomPointInAnnulus);

            isPointValid = this->areaDimensions->contains(randomPointInAnnulus->x(), randomPointInAnnulus->y(), false) &&
                           this->pointIsFarEnoughFromOthers(pointBackgroundGridYIndex, pointBackgroundGridXIndex, randomPointInAnnulus);
            if (isPointValid)
            {
                generatedPoints->append(randomPointInAnnulus);
                activeList->append(randomPointInAnnulus);
                this->backgroundGrid->at(pointBackgroundGridYIndex)->insert(pointBackgroundGridXIndex, randomPointInAnnulus);
            }
        }

        if (!isPointValid)
        {
            activeList->remove(randomActiveListIndex);
        }
    }

    return generatedPoints;
}

QVector<QVector<QVector2D*>*>* PoissonDiskSamplingPointsGenerator::initializeBackgroundGrid()
{
    this->backgroundGridDimensionY = qCeil(this->areaDimensions->height() / minimumPointDistance) + 1;
    this->backgroundGridDimensionX = qCeil(this->areaDimensions->width() / minimumPointDistance) + 1;
    QVector<QVector<QVector2D*>*>* backgoundGrid = new QVector<QVector<QVector2D*>*>(this->backgroundGridDimensionY);
    for (long i = 0; i < backgoundGrid->size(); i++){
        backgoundGrid->insert(i, new QVector<QVector2D*>(this->backgroundGridDimensionX));
    }
    return backgroundGrid;
}

long PoissonDiskSamplingPointsGenerator::pointToBackgroundGridYIndex(QVector2D* point)
{
    return qCeil((point->y() - this->areaDimensions->y()) / this->minimumPointDistance);
}

long PoissonDiskSamplingPointsGenerator::pointToBackgroundGridXIndex(QVector2D* point)
{
    return qCeil((point->x() - this->areaDimensions->x()) / this->minimumPointDistance);
}

QVector2D* PoissonDiskSamplingPointsGenerator::randomPointInAnnulus(QVector2D* point, float innerR, float outerR)
{
    float randomAngle = 2 * M_PI * random->generateDouble();
    float randomRadius = qSqrt((qPow(outerR, 2) - qPow(innerR, 2)) * random->generateDouble() + innerR);
    QVector2D* distanceFromCenter = new QVector2D(randomRadius * qCos(randomAngle), randomRadius * qSin(randomAngle));
    QVector2D* newRandomPoint= new QVector2D(point->x() + distanceFromCenter->x(), point->y() + distanceFromCenter->y());
    return newRandomPoint;
}

bool PoissonDiskSamplingPointsGenerator::pointIsFarEnoughFromOthers(long pointBackgroundGridYIndex,
                                long pointBackgroundGridXIndex, QVector2D* point)
{
    for (long i = -2; i <= 2; i++)
    {
        for (long j = -2; j <= 2; j++)
        {
            long modY = pointBackgroundGridYIndex + i;
            long modX = pointBackgroundGridXIndex + j;

            if (modY >= 0 && modX >= 0 && modY < this->backgroundGridDimensionY && modX < this->backgroundGridDimensionX)
            {
                QVector2D* otherPoint = this->backgroundGrid->at(modY)->at(modX);

                if (!otherPoint && otherPoint->distanceToPoint(*point) < minimumPointDistance)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

