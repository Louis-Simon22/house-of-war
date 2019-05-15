#ifndef TilePainter_H
#define TilePainter_H

#include "../../model/entities/voronoicell.h"
#include "./entitypainter.h"

namespace how {
namespace ui {
class VoronoiCellPainter : public EntityPainter {

public:
  VoronoiCellPainter(model::VoronoiCell &voronoiCell);
  ~VoronoiCellPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  model::VoronoiCell &voronoiCell;
};
} // namespace ui
} // namespace how

#endif // TilePainter_H
