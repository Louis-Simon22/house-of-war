#ifndef TILEDISPLAYSTATUS_H
#define TILEDISPLAYSTATUS_H

#include <QObject>

namespace how {
namespace ui {

class TileDisplayStatusWrapper final : public QObject {
  Q_GADGET

private:
  TileDisplayStatusWrapper();

public:
  enum TileDisplayStatus { TERRAIN, OWNER, DEFAULT = TERRAIN };
  Q_ENUM(TileDisplayStatus)
};

} // namespace ui
} // namespace how

#endif // TILEDISPLAYSTATUS_H
