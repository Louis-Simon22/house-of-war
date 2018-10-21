#include "cell.h"

Cell::Cell(float posX, float posY) : m_posX(posX), m_posY(posY)
{
}

Cell::Cell(QVector2D posV) : m_posX(posV.x()), m_posY(posV.y())
{
}

float Cell::getPosX() const
{
    return this->m_posX;
}

float Cell::getPosY() const
{
    return this->m_posY;
}

QVector2D Cell::getPosV2D() const
{
    return *(new QVector2D(this->m_posX, this->m_posY));
}
