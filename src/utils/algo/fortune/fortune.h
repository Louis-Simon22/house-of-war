#ifndef FORTUNE_H
#define FORTUNE_H

#include <QVector>
#include <QLinkedList>
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
        class Event {
            private:
                float y;
            protected:
                Event(float y): y(y) {}
            public:
                float y()
                {
                    return y;
                }
        };
        class SiteEvent: Event {
            private:
                QVector2D pos;
            public:
                SiteEvent(QVector2D pos) : pos(pos), Event(pos.y()) {}
        };
        class VertexEvent: Event {
            private:
                QVector2D pos1;
                QVector2D pos2;
                QVector2D pos3;

                float lowestCircumcircleYPoint() {
                    // TODO
                    return pos3.y();
                }
            public:
                VertexEvent(QVector2D pos1, QVector2D pos2, QVector2D pos3)
                    : pos1(pos1), pos2(pos2), pos3(pos3), Event(this->lowestCircumcircleYPoint()) {}
        };
};

#endif // FORTUNE_H
