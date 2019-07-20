#ifndef POLYGONPAINTER_H
#define POLYGONPAINTER_H

#include "../../model/entities/terrain/voronoicell.h"
#include "./painteritem.h"

namespace how {
namespace ui {
class PolygonPainter : public PainterItem {

public:
  PolygonPainter(std::vector<types::point_t> points, QQuickItem *parent);
  ~PolygonPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

public:
  void setColor(QColor color);

private:
  QColor color;
  std::vector<types::point_t> points;
};
} // namespace ui
} // namespace how

#endif // POLYGONPAINTER_H
