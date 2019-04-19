#include "segmentspainter.h"

namespace how {
namespace ui {
SegmentsPainter::SegmentsPainter(QQuickItem *parent)
    : QQuickPaintedItem(parent), showVoronoiSegments(false),
      showDelaunaySegments(false) {
  this->setAntialiasing(true);
}

void SegmentsPainter::paint(QPainter *painter) {
  painter->setRenderHints(QPainter::Antialiasing, true);
  if (this->worldDataQMLWrapperPtr) {
    const auto *worldDataPtr = this->worldDataQMLWrapperPtr->getWorldDataPtr();
    if (this->showVoronoiSegments) {
      this->paintSegmentsList(painter,
                              worldDataPtr->getUniqueVoronoiSegments());
    }
    if (this->showDelaunaySegments) {
      this->paintSegmentsList(painter,
                              worldDataPtr->getUniqueDelaunaySegments());
    }
  }
}

void SegmentsPainter::setShowVoronoiSegments(bool show) {
  this->showVoronoiSegments = show;
  this->update();
}

void SegmentsPainter::setShowDelaunaySegments(bool show) {
  this->showDelaunaySegments = show;
  this->update();
}

void SegmentsPainter::setWorldDataQMLWrapper(
    WorldDataQMLWrapper *worldDataQMLWrapperPtr) {
  this->worldDataQMLWrapperPtr = worldDataQMLWrapperPtr;
  this->update();
}

void SegmentsPainter::paintSegmentsList(
    QPainter *painter, const std::vector<types::segment_t> *segments) {
  for (const auto &segment : *segments) {
    painter->drawLine(bg::get<0, 0>(segment), bg::get<0, 1>(segment),
                      bg::get<1, 0>(segment), bg::get<1, 1>(segment));
  }
}
} // namespace ui
} // namespace how
