#ifndef POINTSBASEDSHAPE_H
#define POINTSBASEDSHAPE_H

#include <vector>

#include <QSGGeometryNode>

#include "../../model/modeltypes.h"
#include "./painteritem.h"

namespace how {
namespace ui {
class BasicShapePainter : public PainterItem {
public:
  BasicShapePainter(
      QQuickItem *parent, QSGGeometry::DrawingMode drawingMode, QColor color,
      std::vector<types::point_t> points = std::vector<types::point_t>(),
      float lineWidth = 0);
  ~BasicShapePainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

public:
  void setColor(QColor color);
  void setPoints(std::vector<types::point_t> points);
  void clearPoints();
  void setLineWidth(float lineWidth);

private:
  std::vector<types::point_t> points;
  bool pointsChanged;
  QColor color;
  QSGGeometry::DrawingMode drawingMode;
  float lineWidth;
};
} // namespace ui
} // namespace how

#endif // POINTSBASEDSHAPE_H
