#ifndef VORONOICELLITEM_H
#define VORONOICELLITEM_H

#include "../../model/entities/voronoicell.h"
#include "../painters/painteritem.h"
#include "../painters/polygonpainter.h"
#include "./graphentityitem.h"

namespace how {
namespace ui {
class VoronoiCellItem : public GraphEntityItem {
public:
  VoronoiCellItem(std::shared_ptr<model::VoronoiCell> voronoiCellPtr,
                  QQuickItem *parent);

private slots:
  void onGraphEntityUpdated() override;

private:
  std::shared_ptr<model::VoronoiCell> voronoiCellPtr;
  PolygonPainter *voronoiCellPainter;
};
} // namespace ui
} // namespace how

#endif // VORONOICELLITEM_H
