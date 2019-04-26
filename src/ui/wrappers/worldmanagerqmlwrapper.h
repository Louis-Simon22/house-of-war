#ifndef WorldManagerQMLWRAPPER_H
#define WorldManagerQMLWRAPPER_H

#include <memory>

#include <QObject>
#include <QRect>

#include "../../model/graphtypes.h"
#include "../../model/managers/worldmanager.h"
#include "../../model/modeltypes.h"
#include "../models/voronoicellsmodel.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
} // namespace
class WorldManagerQMLWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(QRect worldBounds READ getWorldBounds CONSTANT)
  Q_PROPERTY(
      VoronoiCellsModel *voronoiCellsModel READ getVoronoiCellsModel CONSTANT)

public:
  WorldManagerQMLWrapper();
  explicit WorldManagerQMLWrapper(model::WorldManager *WorldManagerPtr);

  Q_INVOKABLE int cellIndexAtPosition(int pointX, int pointY);

private:
  const QRect getWorldBounds() const;
  VoronoiCellsModel *getVoronoiCellsModel() const;

public:
  const model::WorldManager *getWorldManagerPtr() const;
  const model::VoronoiCell &getVoronoiCellAt(int index) const;

private:
  const model::WorldManager *worldManagerPtr;
};
} // namespace ui
} // namespace how

#endif // QMLBINDINGS_H
