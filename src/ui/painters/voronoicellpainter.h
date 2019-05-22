#ifndef TilePainter_H
#define TilePainter_H

#include "../../model/entities/voronoicell.h"
#include "./entitypainter.h"

namespace how {
namespace ui {
class VoronoiCellPainter : public EntityPainter {

public:
  VoronoiCellPainter(QQuickItem *parent,
                     std::shared_ptr<model::VoronoiCell> voronoiCellPtr);
  ~VoronoiCellPainter() override;

public:
  void updateDimensions() override;
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  std::shared_ptr<model::VoronoiCell> voronoiCellPtr;
};
} // namespace ui
} // namespace how

#endif // TilePainter_H
