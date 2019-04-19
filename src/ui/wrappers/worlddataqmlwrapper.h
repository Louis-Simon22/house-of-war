#ifndef WORLDDATAQMLWRAPPER_H
#define WORLDDATAQMLWRAPPER_H

#include <memory>

#include <QObject>
#include <QRect>

#include "../../model/graphtypes.h"
#include "../../model/modeltypes.h"
#include "../../model/world/worlddata.h"
#include "../models/voronoicellsmodel.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
} // namespace
class WorldDataQMLWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(const QRect worldBounds READ getWorldBounds CONSTANT)
  Q_PROPERTY(
      VoronoiCellsModel *voronoiCellsModel READ getVoronoiCellsModel CONSTANT)

public:
  WorldDataQMLWrapper();
  explicit WorldDataQMLWrapper(model::WorldData *worldDataPtr);

  Q_INVOKABLE int cellDescAtPosition(int pointX, int pointY);

private:
  const QRect getWorldBounds() const;
  VoronoiCellsModel *getVoronoiCellsModel() const;

public:
  const model::WorldData *getWorldDataPtr() const;
  const model::VoronoiCell *getVoronoiCellAt(int index) const;

private:
  model::WorldData *worldDataPtr;
};
} // namespace ui
} // namespace how

#endif // QMLBINDINGS_H
