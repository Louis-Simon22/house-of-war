#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <memory>

#include <QAbstractListModel>
#include <QVariant>

#include "../../model/modeltypes.h"

namespace how {
namespace bind {
namespace {
using point_t = ::how::model::types::point_t;
namespace bg = ::boost::geometry;
} // namespace
class WorldModel : public QAbstractListModel {
  Q_OBJECT
public:
  WorldModel();
  explicit WorldModel(const std::vector<point_t> *points);

  enum CellRoles { PosX = Qt::UserRole + 1, PosY };

  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex &) const override;
  QVariant headerData(int, Qt::Orientation, int) const override;
  int rowCount(const QModelIndex &) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

private:
  const std::vector<point_t> *points;
};
} // namespace bind
} // namespace how

#endif
