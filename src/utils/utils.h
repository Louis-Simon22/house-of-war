#ifndef UTILS_H
#define UTILS_H

#include <QRandomGenerator>

namespace utils
{
    double randomBoundedDouble(QRandomGenerator& random, double lower, double higher);
    float randomBoundedFloat(QRandomGenerator& random, float lower, float higher);
}

#endif // UTILS_H
