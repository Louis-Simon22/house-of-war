#ifndef TILESCONTROLLER_H
#define TILESCONTROLLER_H

#include <QObject>

#include "../items/tiledisplaystatus.h"

namespace how {
namespace ui {
class TilesController : public QObject {
  Q_OBJECT

  Q_PROPERTY(int tileDisplayStatus READ getTileDisplayStatus WRITE
                 setTileDisplayStatus NOTIFY onTileDisplayStatusChanged FINAL)

public:
  TilesController();

signals:
  void onTileDisplayStatusChanged();

public:
  TileDisplayStatusWrapper::TileDisplayStatus getTileDisplayStatus() const;

private:
  void setTileDisplayStatus(int tileDisplayStatus);

private:
  TileDisplayStatusWrapper::TileDisplayStatus currentTileDisplayStatus;
};
} // namespace ui
} // namespace how

#endif // TILESCONTROLLER_H
