#ifndef TILESCONTROLLER_H
#define TILESCONTROLLER_H

#include <QObject>
#include <QString>

#include "../items/tiledisplaystatus.h"
#include "./terraintypewrapper.h"

namespace how {
namespace ui {
class TilesController : public QObject {
  Q_OBJECT

  Q_PROPERTY(int tileDisplayStatus READ getTileDisplayStatus WRITE
                 setTileDisplayStatus NOTIFY onTileDisplayStatusChanged FINAL)
  Q_PROPERTY(int terrainType MEMBER currentTerrainType NOTIFY
                 onTerrainTypeChanged FINAL)

public:
  TilesController();

signals:
  void onTileDisplayStatusChanged();
  void onTerrainTypeChanged(int terrainType);

public:
  TileDisplayStatusWrapper::TileDisplayStatus getTileDisplayStatus() const;
  model::TerrainType getTerrainType() const;

private:
  void setTileDisplayStatus(int tileDisplayStatus);

private:
  TileDisplayStatusWrapper::TileDisplayStatus currentTileDisplayStatus;
  int currentTerrainType;
};
} // namespace ui
} // namespace how

#endif // TILESCONTROLLER_H
