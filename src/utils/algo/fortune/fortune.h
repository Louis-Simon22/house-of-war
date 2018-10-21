#ifndef FORTUNE_H
#define FORTUNE_H

#include <QVector>
#include <QPolygonF>
#include <QVector2D>
#include <memory>
#include <queue>
#include <iostream>

using namespace std;

class Fortune
{
    public:
        Fortune(QVector<QVector2D> points);
        QVector<QPolygonF> sweep();

   private:
        QVector<QVector2D> points;
};

#endif // FORTUNE_H
