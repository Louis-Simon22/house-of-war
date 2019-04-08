#ifndef CELLSMODEL_H
#define CELLSMODEL_H

#include <memory>

#include <QAbstractListModel>
#include <QVariant>

#include "./entitymodel.h"
#include "../../model/world/voronoicell.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
} // namespace
class VoronoiCellsModel : public EntityModel {
  Q_OBJECT

public:
  VoronoiCellsModel();
  explicit VoronoiCellsModel(const std::vector<model::VoronoiCell> *const voronoiCellsPtr);

  enum CellRoles { Centroid = Qt::UserRole + 1, Points, Envelope };

  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex &) const override;
  QVariant headerData(int, Qt::Orientation, int) const override;
  int rowCount(const QModelIndex &) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

private:
  const std::vector<model::VoronoiCell> *const voronoiCellsPtr;
};
} // namespace ui
} // namespace how

#endif
