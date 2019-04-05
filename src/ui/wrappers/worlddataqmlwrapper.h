#ifndef WORLDDATAQMLWRAPPER_H
#define WORLDDATAQMLWRAPPER_H

#include <memory>

#include <QList>
#include <QObject>
#include <QPoint>
#include <QQmlEngine>
#include <QRect>
#include <QVariant>

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

  Q_PROPERTY(
      const QList<QVariant> outlineSegments READ getOutlineSegments CONSTANT)
  Q_PROPERTY(const QList<QVariant> pathSegments READ getPathSegments CONSTANT)
  Q_PROPERTY(const QRect worldBounds READ getWorldBounds CONSTANT)
  Q_PROPERTY(
      VoronoiCellsModel *voronoiCellsModel READ getVoronoiCellsModel CONSTANT)

public:
  WorldDataQMLWrapper();
  explicit WorldDataQMLWrapper(model::WorldData *worldDataPtr);

  Q_INVOKABLE bool isPointWithinVoronoiCell(int voronoiCellIndex, int pointX,
                                            int pointY);

private:
  const QRect getWorldBounds() const;
  const QList<QVariant> getOutlineSegments() const;
  const QList<QVariant> getPathSegments() const;
  VoronoiCellsModel *getVoronoiCellsModel() const;

private:
  model::WorldData *worldDataPtr;
};
} // namespace ui
} // namespace how

#endif // QMLBINDINGS_H
