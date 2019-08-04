#ifndef TERRAINTYPEWRAPPER_H
#define TERRAINTYPEWRAPPER_H

#include <QObject>

#include "../../model/entities/terrain/terraintype.h"

namespace how {
namespace ui {
class TerrainTypeWrapper final : public QObject {
  Q_GADGET

private:
  TerrainTypeWrapper();

public:
  enum TerrainType { FOREST = 0, MOUNTAIN, PLAIN, DEFAULT = PLAIN };
  Q_ENUM(TerrainType)
};
} // namespace ui
} // namespace how

#endif // TERRAINTYPEWRAPPER_H
