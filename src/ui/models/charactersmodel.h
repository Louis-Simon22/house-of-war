#ifndef CHARACTERSMODEL_H
#define CHARACTERSMODEL_H

#include "../../model/managers/graphentitymanager.h"
#include "./entitymodel.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
} // namespace
class CharactersModel : public EntityModel {
  Q_OBJECT

public:
  CharactersModel();
  explicit CharactersModel(
      const model::GraphEntityManager *graphEntityManagerPtr);

  enum CellRoles { PosX = Qt::UserRole + 1, PosY };

  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex &) const override;
  QVariant headerData(int, Qt::Orientation, int) const override;
  int rowCount(const QModelIndex &) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

private:
  const model::GraphEntityManager *graphEntityManagerPtr;
};
} // namespace ui
} // namespace how

#endif
