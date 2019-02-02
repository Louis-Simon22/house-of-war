#include "pathspainter.h"

namespace how {
namespace bind {
PathsPainter::PathsPainter(QQuickItem *parent)
    : QQuickPaintedItem(parent), segments(QList<QVariant>()) {
  this->setAntialiasing(true);
}

void PathsPainter::paint(QPainter *painter) {
  painter->setRenderHints(QPainter::Antialiasing, true);
  for (const QVariant &segment : this->segments) {
    const QList<QVariant> points = segment.toList();
    const QPoint p1 = points[0].toPoint();
    const QPoint p2 = points[1].toPoint();
    painter->drawLine(p1, p2);
  }
}

void PathsPainter::setSegments(const QList<QVariant> segments) {
  this->segments = segments;
}
} // namespace bind
} // namespace how
