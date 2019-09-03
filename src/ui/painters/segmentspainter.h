#ifndef CELLOUTLINESPAINTER_H
#define CELLOUTLINESPAINTER_H

#include <QPainter>

#include "../../model/modeltypes.h"
#include "./painteritem.h"

namespace how {
namespace ui {

class SegmentsPainter : public PainterItem {
  Q_OBJECT

public:
  SegmentsPainter(const std::vector<types::segment_t> &segments,
                  QQuickItem *parent);

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  const std::vector<types::segment_t> &segments;
};

} // namespace ui
} // namespace how

#endif
