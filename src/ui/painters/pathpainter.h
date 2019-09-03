#ifndef PATHPAINTER_H
#define PATHPAINTER_H

#include <vector>

#include <QColor>

#include "../../model/entities/change/entitypositionchange.h"
#include "./painteritem.h"

namespace how {
namespace ui {
class PathPainter: public PainterItem {
public:
  PathPainter(std::vector<types::point_t> points, QQuickItem *parent);
  ~PathPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

public:
  void setPoints(std::vector<types::point_t> points);

private:
  QColor color;
  std::vector<types::point_t> points;
};
} // namespace ui
} // namespace how

#endif // PATHPAINTER_H
