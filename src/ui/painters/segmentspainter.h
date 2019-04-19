#ifndef CELLOUTLINESPAINTER_H
#define CELLOUTLINESPAINTER_H

#include <QPainter>
#include <QQuickPaintedItem>

#include "../wrappers/worlddataqmlwrapper.h"

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
  Q_PROPERTY(WorldDataQMLWrapper *worldData MEMBER worldDataQMLWrapperPtr
                 WRITE setWorldDataQMLWrapper FINAL)

public:
  SegmentsPainter(QQuickItem *parent = nullptr);

public:
  void paint(QPainter *painter) override;

private:
  void setShowVoronoiSegments(bool show);
  void setShowDelaunaySegments(bool show);
  void setWorldDataQMLWrapper(WorldDataQMLWrapper *worldDataPtr);
  static void paintSegmentsList(QPainter *painter,
                         const std::vector<types::segment_t> *segments);

private:
  WorldDataQMLWrapper *worldDataQMLWrapperPtr;
  bool showVoronoiSegments;
  bool showDelaunaySegments;
};

} // namespace ui
} // namespace how

#endif
