#ifndef CELLOUTLINESPAINTER_H
#define CELLOUTLINESPAINTER_H

#include <QPainter>
#include <QQuickPaintedItem>

#include "../../model/managers/worldmanager.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

class SegmentsPainter : public QQuickPaintedItem {
  Q_OBJECT

  Q_PROPERTY(bool showVoronoiSegments MEMBER showVoronoiSegments WRITE
                 setShowVoronoiSegments FINAL)
  Q_PROPERTY(bool showDelaunaySegments MEMBER showDelaunaySegments WRITE
                 setShowDelaunaySegments FINAL)

public:
  SegmentsPainter(const model::WorldManager &worldManager);

public:
  void paint(QPainter *painter) override;

private:
  void setShowVoronoiSegments(bool show);
  void setShowDelaunaySegments(bool show);
  static void paintSegmentsList(QPainter *painter,
                                const std::vector<types::segment_t> &segments);

private:
  const model::WorldManager &worldManager;
  bool showVoronoiSegments;
  bool showDelaunaySegments;
};

} // namespace ui
} // namespace how

#endif
