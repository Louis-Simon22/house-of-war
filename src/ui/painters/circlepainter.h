#ifndef ARMYPAINTER_H
#define ARMYPAINTER_H

#include "./painteritem.h"

namespace how {
namespace ui {
class CirclePainter : public PainterItem {
  Q_OBJECT

public:
  CirclePainter(QQuickItem *parent, float lineWidth, QColor color);
  ~CirclePainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

public:
  void setLineWidth(float lineWidth);
  void setColor(QColor color);
  void setRadius(float radius);

private:
  float lineWidth;
  QColor color;
  float radius;
};
} // namespace ui
} // namespace how

#endif // ARMYPAINTER_H
