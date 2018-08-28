#include "utils.h"

double utils::randomBoundedDouble(QRandomGenerator* random, double lower, double higher)
{
    return random->generateDouble() * (higher - lower) + lower;
}

float utils::randomBoundedFloat(QRandomGenerator* random, float lower, float higher)
{
    return ((float) random->generateDouble()) * (higher - lower) + lower;
}
