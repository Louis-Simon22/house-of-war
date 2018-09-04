#ifndef CELL_H
#define CELL_H

#include <QPoint>
#include <QVector2D>

class Cell
{
    public:
        Cell(int posX, int posY);
        Cell(QVector2D* posV);
        Cell(QPoint* pos);

        int x();
        int y();
        QPoint* pos();
        QVector2D* posV();

    private:
        int posX;
        int posY;
};

#endif // CELL_H
