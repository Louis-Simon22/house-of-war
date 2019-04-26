#include "armiesmodel.h"

namespace how {
namespace ui {

ArmiesModel::ArmiesModel() : EntityModel(), graphEntityManagerPtr(nullptr) {}

ArmiesModel::ArmiesModel(const model::GraphEntityManager *graphEntityManagerPtr)
    : EntityModel(), graphEntityManagerPtr(graphEntityManagerPtr) {
  const auto &armies = graphEntityManagerPtr->getArmies();
  for (std::size_t i = 0; i < armies.size(); i++) {
    this->uuidToIndexMap[armies[i].getUuid()] =
        this->index(static_cast<int>(i));
  }
}

QHash<int, QByteArray> ArmiesModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[PosX] = "posX";
  roles[PosY] = "posY";
  return roles;
}

Qt::ItemFlags ArmiesModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable;
}

QVariant ArmiesModel::headerData(int, Qt::Orientation, int) const {
  return QVariant();
}

int ArmiesModel::rowCount(const QModelIndex &) const {
  return static_cast<int>(this->graphEntityManagerPtr->getCharacters().size());
}

QVariant ArmiesModel::data(const QModelIndex &index, int role) const {
  const auto &army = this->graphEntityManagerPtr
                         ->getArmies()[static_cast<std::size_t>(index.row())];
  switch (role) {
  case PosX:
    return bg::get<0>(army.getPosition());
  case PosY:
    return bg::get<1>(army.getPosition());
  default:
    return 0;
  }
}

} // namespace ui
} // namespace how
