#ifndef CELLSMODEL_H
#define CELLSMODEL_H

#include <memory>
#include <vector>

#include <QAbstractItemModel>

#include "../wrappers/entitywrapper.h"

namespace how {
namespace ui {
namespace {
namespace uuids = ::boost::uuids;
}
class EntitiesModel : public QAbstractItemModel {
  Q_OBJECT

public:
  EntitiesModel();
  explicit EntitiesModel(
      const std::vector<std::unique_ptr<EntityWrapper>> *entityWrappersPtr);
  ~EntitiesModel() override;

private:
  enum EntityRoles {
    RolePosX = Qt::UserRole + 1,
    RolePosY,
    RoleWidth,
    RoleHeight,
    RoleLayer,
    RoleAcceptedButtons
  };

public:
  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex &) const override;
  QVariant headerData(int, Qt::Orientation, int) const override;
  QModelIndex index(int row, int column, const QModelIndex &) const override;
  QModelIndex parent(const QModelIndex &) const override;
  int columnCount(const QModelIndex &) const override;
  int rowCount(const QModelIndex &) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

public:
  void entityChanged(const uuids::uuid &uuid);

private:
  const std::vector<std::unique_ptr<EntityWrapper>> *entityWrappersPtr;
  std::map<const uuids::uuid, QModelIndex> uuidToIndexMap;
};
} // namespace ui
} // namespace how

#endif
