#ifndef TILEITEM_H
#define TILEITEM_H

#include "../../model/entities/tile.h"
#include "../../model/modeltypes.h"
#include "../painters/polygonoutlinepainter.h"
#include "../painters/polygonpainter.h"
#include "./entityitem.h"

namespace how {
namespace ui {
class TileItem : public EntityItem {
  Q_OBJECT

public:
  TileItem(model::Tile *tile, QQuickItem *parent);

signals:
  void onVoronoiCellItemSelected(TileItem *voronoiCellItem);

private slots:
  void onGraphEntityUpdated() override;

private:
  const model::Tile *tile;
  PolygonPainter *voronoiCellPainter;
  PolygonOutlinePainter *voronoiCellOutlinePainter;
};
} // namespace ui
} // namespace how

#endif // TILEITEM_H
