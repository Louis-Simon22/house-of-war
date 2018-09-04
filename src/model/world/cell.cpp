#include "cell.h"

Cell::Cell(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}

Cell::Cell(QVector2D *posV)
{
    Cell(posV->x(), posV->y());
}

Cell::Cell(QPoint *pos)
{
    Cell(pos->x(), pos->y());
}

int Cell::x()
{
    return posX;
}

int Cell::y()
{
    return posY;
}

QPoint *Cell::pos()
{
    return new QPoint(posX, posY);
}

QVector2D *Cell::posV()
{
    return new QVector2D(posX, posY);
}
