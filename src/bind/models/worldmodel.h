#ifndef MAP_H
#define MAP_H

#include <QAbstractListModel>
#include <QVariant>
#include <memory>
#include "../../model/modeltypes.h"

namespace how {
namespace bind {
namespace models {
namespace bg = ::boost::geometry;
class WorldModel : public QAbstractListModel {
  using point_t = ::how::model::types::point_t;
  Q_OBJECT
 public:
  WorldModel();
  WorldModel(const std::vector<point_t>& points);
  enum CellRoles { PosX = Qt::UserRole + 1, PosY };

  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex&) const override;
  QVariant headerData(int, Qt::Orientation, int) const override;
  int rowCount(const QModelIndex&) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;

 private:
  const std::vector<point_t>& points;
};
}  // namespace models
}  // namespace bind
}  // namespace how

#endif
