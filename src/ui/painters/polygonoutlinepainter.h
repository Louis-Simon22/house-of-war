#ifndef POLYGONOUTLINEPAINTER_H
#define POLYGONOUTLINEPAINTER_H

#include "../../model/entities/terrain/voronoicell.h"
#include "./painteritem.h"

namespace how {
namespace ui {
class PolygonOutlinePainter : public PainterItem {

public:
  PolygonOutlinePainter(QQuickItem *parent, std::vector<types::point_t> points);
  ~PolygonOutlinePainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

public:
  void setColor(QColor color);

private:
  std::vector<types::point_t> points;
  QColor color;
};
} // namespace ui
} // namespace how

#endif // POLYGONOUTLINEPAINTER_H
