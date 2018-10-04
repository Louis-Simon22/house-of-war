#include "poissondisksamplingpointsgenerator.h"

#include <QtMath>
#include "../../utils/utils.h"

#include <QDebug>
#include <cmath>
#include <cmath>


using namespace std;
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
    QVector<QVector2D*>* activePoints = new QVector<QVector2D*>();
    generatedPoints->append(initialPoint);
    activePoints->append(initialPoint);

    long backgroundYIndex = this->pointToBackgroundGridYIndex(initialPoint);
    long backgroundXIndex = this->pointToBackgroundGridXIndex(initialPoint);
    this->backgroundGrid->at(backgroundYIndex)
            ->replace(backgroundXIndex, initialPoint);
    int limit = 0;
    while (!activePoints->isEmpty() && limit++ < 10000)
    {
        long randomActiveListIndex = this->random->bounded(0, activePoints->size());
        bool isPointValid = false;
        for (long i = 0; i < this->maximumGenerationAttempts && !isPointValid; i++)
        {
            QVector2D* randomPointInAnnulus = this->randomPointInAnnulus(activePoints->at(randomActiveListIndex),
                                                                         this->minimumPointDistance,
                                                                         this->minimumPointDistance * 2.0f);
            long pointBackgroundGridYIndex = this->pointToBackgroundGridYIndex(randomPointInAnnulus);
            long pointBackgroundGridXIndex = this->pointToBackgroundGridXIndex(randomPointInAnnulus);

            bool isPointValid = this->areaDimensions->contains(randomPointInAnnulus->x(), randomPointInAnnulus->y(), true) &&
                           this->pointIsFarEnoughFromOthers(pointBackgroundGridYIndex, pointBackgroundGridXIndex, randomPointInAnnulus);
            if (isPointValid)
            {
                generatedPoints->append(randomPointInAnnulus);
                activePoints->append(randomPointInAnnulus);
                this->backgroundGrid->at(pointBackgroundGridYIndex)->replace(pointBackgroundGridXIndex, randomPointInAnnulus);
            }
        }

        if (!isPointValid)
        {
            activePoints->remove(randomActiveListIndex);
        }
    }

    return generatedPoints;
}

QVector<QVector<QVector2D*>*>* PoissonDiskSamplingPointsGenerator::initializeBackgroundGrid()
{
    this->backgroundGridDimensionY = ceil(this->areaDimensions->height() / this->minimumPointDistance) + 1;
    this->backgroundGridDimensionX = ceil(this->areaDimensions->width() / this->minimumPointDistance) + 1;
    QVector<QVector<QVector2D*>*>* backgroundGrid = new QVector<QVector<QVector2D*>*>(this->backgroundGridDimensionY);
    for (long i = 0; i < backgroundGrid->size(); i++){
        backgroundGrid->replace(i, new QVector<QVector2D*>(this->backgroundGridDimensionX));
    }
    return backgroundGrid;
}

long PoissonDiskSamplingPointsGenerator::pointToBackgroundGridYIndex(QVector2D* point)
{
    return ceil((point->y() - this->areaDimensions->y()) / this->minimumPointDistance);
}

long PoissonDiskSamplingPointsGenerator::pointToBackgroundGridXIndex(QVector2D* point)
{
    return ceil((point->x() - this->areaDimensions->x()) / this->minimumPointDistance);
}

QVector2D* PoissonDiskSamplingPointsGenerator::randomPointInAnnulus(QVector2D* point, float innerR, float outerR)
{
    float randomAngle = 2 * M_PI * random->generateDouble();
    float randomRadius = ((outerR - innerR) * random->generateDouble()) + innerR;
    float xTranslationFromCenter = randomRadius * cos(randomAngle);
    float yTranslationFromCenter = randomRadius * sin(randomAngle);
    return new QVector2D(point->x() + xTranslationFromCenter, point->y() + yTranslationFromCenter);
}

bool PoissonDiskSamplingPointsGenerator::pointIsFarEnoughFromOthers(long pointBackgroundGridYIndex,
                                long pointBackgroundGridXIndex, QVector2D* point)
{
    for (long i = -2; i <= 2; i++)
    {
        long modY = pointBackgroundGridYIndex + i;
        for (long j = -2; j <= 2; j++)
        {
            long modX = pointBackgroundGridXIndex + j;

            if (modY >= 0 && modX >= 0 && modY < this->backgroundGridDimensionY && modX < this->backgroundGridDimensionX)
            {
                QVector2D* otherPoint = this->backgroundGrid->at(modY)->at(modX);

                if (otherPoint && otherPoint->distanceToPoint(*point) < this->minimumPointDistance)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

