#ifndef TILEITEM_H
#define TILEITEM_H

#include "../../model/entities/terrain/tile.h"
#include "../../model/modeltypes.h"
#include "../control/tilescontroller.h"
#include "../painters/basicshapepainter.h"
#include "./entityitem.h"

namespace how {
namespace ui {
class TileItem : public EntityItem {
  Q_OBJECT

  constexpr static float SELECTION_OUTLINE_WIDTH = 4;

public:
  TileItem(model::Tile *tile, const TilesController *tilesController,
           QQuickItem *parent);
  ~TileItem() override;

public slots:
  void onTileDisplayStatusChanged();

private slots:
  void onGraphEntityUpdated() override;

private:
  const model::Tile *tile;
  const TilesController *tilesController;
  BasicShapePainter *voronoiCellPainter;
  BasicShapePainter *selectionOutlinePainter;
};
} // namespace ui
} // namespace how

#endif // TILEITEM_H
