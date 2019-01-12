#ifndef EDGESMODEL_H
#define EDGESMODEL_H

#include <memory>

#include <QAbstractListModel>
#include <QVariant>

#include "../../model/modeltypes.h"

namespace how {
namespace bind {
namespace models {
namespace {
using point_t = ::how::model::types::point_t;
using vd_t = ::how::model::types::vd_t;
namespace bg = ::boost::geometry;
} // namespace
class EdgesModel : public QAbstractListModel {
  Q_OBJECT
public:
  EdgesModel();
  explicit EdgesModel(const vd_t *vd);

  enum CellRoles { PosX1 = Qt::UserRole + 1, PosY1, PosX2, PosY2 };

  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex &) const override;
  QVariant headerData(int, Qt::Orientation, int) const override;
  int rowCount(const QModelIndex &) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

private:
  const vd_t *vd;
};
} // namespace models
} // namespace bind
} // namespace how

#endif
