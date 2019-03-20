#include "segmentspainter.h"

namespace how {
namespace ui {
SegmentsPainter::SegmentsPainter(QQuickItem *parent)
    : QQuickPaintedItem(parent), segments(QList<QVariant>()) {
  this->setAntialiasing(true);
  this->setVisible(false);
}

void SegmentsPainter::paint(QPainter *painter) {
  painter->setRenderHints(QPainter::Antialiasing, true);
  for (const QVariant &segment : this->segments) {
    const QList<QVariant> points = segment.toList();
    const QPoint p1 = points[0].toPoint();
    const QPoint p2 = points[1].toPoint();
    painter->drawLine(p1, p2);
  }
}

void SegmentsPainter::setSegments(const QList<QVariant> segments) {
  this->segments = segments;
  this->setVisible(segments.size() > 0);
}
} // namespace ui
} // namespace how
