#ifndef TILEDISPLAYSTATUS_H
#define TILEDISPLAYSTATUS_H

#include <QObject>

namespace how {
namespace ui {

class TileDisplayStatusWrapper : public QObject {
  Q_GADGET

public:
  TileDisplayStatusWrapper();
  ~TileDisplayStatusWrapper();

public:
  enum TileDisplayStatus {
    TILE_DISPLAY_STATUS_TERRAIN,
    TILE_DISPLAY_STATUS_OWNER,
    TILE_DISPLAY_STATUS_DEFAULT = TILE_DISPLAY_STATUS_TERRAIN
  };
  Q_ENUM(TileDisplayStatus)
};

} // namespace ui
} // namespace how

#endif // TILEDISPLAYSTATUS_H
