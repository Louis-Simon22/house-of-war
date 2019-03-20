#ifndef CELLOUTLINESPAINTER_H
#define CELLOUTLINESPAINTER_H

#include <QList>
#include <QPainter>
#include <QPoint>
#include <QQuickPaintedItem>
#include <QVariant>

namespace how {
namespace ui {

class SegmentsPainter : public QQuickPaintedItem {
  Q_OBJECT

  Q_PROPERTY(const QList<QVariant> segments WRITE setSegments)

public:
  SegmentsPainter(QQuickItem *parent = nullptr);

  void paint(QPainter *painter) override;

private:
  QList<QVariant> segments;

  void setSegments(const QList<QVariant>);
};

} // namespace bind
} // namespace how

#endif
