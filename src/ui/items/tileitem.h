#ifndef TILEITEM_H
#define TILEITEM_H

#include "../../model/entities/terrain/tile.h"
#include "../../model/modeltypes.h"
#include "../control/tilescontroller.h"
#include "../painters/polygonoutlinepainter.h"
#include "../painters/polygonpainter.h"
#include "./entityitem.h"

namespace how {
namespace ui {
class TileItem : public EntityItem {
  Q_OBJECT

public:
  TileItem(model::Tile *tile, const TilesController *tilesController,
           QQuickItem *parent);

public slots:
  void onTileDisplayStatusChanged();

private slots:
  void onGraphEntityUpdated() override;

private:
  const model::Tile *tile;
  const TilesController *tilesController;
  PolygonPainter *voronoiCellPainter;
  PolygonOutlinePainter *voronoiCellOutlinePainter;
};
} // namespace ui
} // namespace how

#endif // TILEITEM_H
