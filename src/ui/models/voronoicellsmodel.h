#ifndef CELLSMODEL_H
#define CELLSMODEL_H

#include "../../model/managers/worldmanager.h"
#include "./entitymodel.h"

namespace how {
namespace ui {
class VoronoiCellsModel : public EntityModel {
  Q_OBJECT

public:
  VoronoiCellsModel();
  explicit VoronoiCellsModel(const model::WorldManager *WorldManagerPtr);

  enum CellRoles { Envelope = Qt::UserRole + 1 };

  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex &) const override;
  QVariant headerData(int, Qt::Orientation, int) const override;
  int rowCount(const QModelIndex &) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

private:
  const model::WorldManager *WorldManagerPtr;
};
} // namespace ui
} // namespace how

#endif
