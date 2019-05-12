#ifndef TilePainter_H
#define TilePainter_H

#include "../wrappers/voronoicellwrapper.h"
#include "./entitypainter.h"

namespace how {
namespace ui {
class VoronoiCellPainter : public EntityPainter {

public:
  VoronoiCellPainter(const VoronoiCellWrapper& voronoiCellWrapper);
  ~VoronoiCellPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  const VoronoiCellWrapper& voronoiCellWrapper;
};
} // namespace ui
} // namespace how

#endif // TilePainter_H
