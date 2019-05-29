#ifndef CHARACTERPAINTER_H
#define CHARACTERPAINTER_H

#include "./painteritem.h"

namespace how {
namespace ui {
class RectanglePainter : public PainterItem {
public:
  RectanglePainter(QQuickItem *parent, QColor color);
  ~RectanglePainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

public:
  void setColor(QColor color);

private:
  QColor color;
};
} // namespace ui
} // namespace how

#endif // CHARACTERPAINTER_H
