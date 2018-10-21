#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QPoint>
#include <QVector2D>

class Cell : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float posX READ getPosX CONSTANT)
    Q_PROPERTY(float posY READ getPosY CONSTANT)

    public:
        Cell(float posX, float posY);
        Cell(QVector2D getPosV2D);

        float getPosX() const;
        float getPosY() const;
        QVector2D getPosV2D() const;

    private:
        float m_posX;
        float m_posY;
};

#endif // CELL_H
