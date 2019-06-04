#ifndef CELLOUTLINESPAINTER_H
#define CELLOUTLINESPAINTER_H

#include <QPainter>
#include <QQuickItem>

#include "../../model/modeltypes.h"

namespace how {
namespace ui {

class SegmentsPainter : public QQuickItem {
  Q_OBJECT

public:
  SegmentsPainter(QQuickItem *parent,
                  const std::vector<types::segment_t> &segments);

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  const std::vector<types::segment_t> &segments;
};

} // namespace ui
} // namespace how

#endif
