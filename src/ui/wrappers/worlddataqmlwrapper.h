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
#include "../models/cellsmodel.h"

namespace how {
namespace ui {
namespace bg = ::boost::geometry;
namespace {
using WorldData = ::how::model::WorldData;
} // namespace
class WorldDataQMLWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      const QList<QVariant> outlineSegments READ getOutlineSegments CONSTANT)
  Q_PROPERTY(const QList<QVariant> pathSegments READ getPathSegments CONSTANT)
  Q_PROPERTY(const QRect worldBounds READ getWorldBounds CONSTANT)
  Q_PROPERTY(CellsModel *cellsModel READ getCellsModel CONSTANT)

public:
  WorldDataQMLWrapper();
  explicit WorldDataQMLWrapper(WorldData *worldDataPtr);

private:
  const QList<QVariant> getOutlineSegments() const;
  const QList<QVariant> getPathSegments() const;
  const QRect getWorldBounds() const;
  CellsModel *getCellsModel() const;

private:
  WorldData *worldDataPtr;

  const QList<QVariant> static convert(
      const std::vector<model::types::segment_t> *segments);
};
} // namespace ui
} // namespace how

#endif // QMLBINDINGS_H
