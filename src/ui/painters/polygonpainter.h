#ifndef TilePainter_H
#define TilePainter_H

#include "../../model/entities/voronoicell.h"
#include "./painteritem.h"

namespace how {
namespace ui {
class PolygonPainter : public PainterItem {

public:
  PolygonPainter(QQuickItem *parent, std::vector<types::point_t> points);
  ~PolygonPainter() override;

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

#endif // TilePainter_H
