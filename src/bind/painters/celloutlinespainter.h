#ifndef CELLOUTLINEPAINTER_H
#define CELLOUTLINEPAINTER_H

#include <QList>
#include <QPainter>
#include <QPoint>
#include <QQuickPaintedItem>
#include <QVariant>

namespace how {
namespace bind {

class CellOutlinesPainter : public QQuickPaintedItem {
  Q_OBJECT

  Q_PROPERTY(const QList<QVariant> segments WRITE setSegments)

public:
  CellOutlinesPainter(QQuickItem *parent = nullptr);

  void paint(QPainter *painter) override;

private:
  QList<QVariant> segments;

  void setSegments(const QList<QVariant>);
};

} // namespace bind
} // namespace how

#endif
