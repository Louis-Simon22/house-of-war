#include "entitiesmodel.h"

#include "../conversion/converter.h"

#include <iostream>

namespace how {
namespace ui {

EntitiesModel::EntitiesModel()
    : QAbstractItemModel(), entityWrappersPtr(nullptr), uuidToIndexMap() {}

EntitiesModel::EntitiesModel(
    const std::vector<std::unique_ptr<EntityWrapper>> *entityWrappersPtr)
    : entityWrappersPtr(entityWrappersPtr), uuidToIndexMap() {
  for (std::size_t i = 0; i < entityWrappersPtr->size(); i++) {
    this->uuidToIndexMap[entityWrappersPtr->operator[](i)->getEntityUuid()] =
        this->index(static_cast<int>(i), 0, QModelIndex());
  }
}

EntitiesModel::~EntitiesModel() {}

QHash<int, QByteArray> EntitiesModel::roleNames() const {
  auto roles = QHash<int, QByteArray>();
  roles[RolePosX] = "rolePosX";
  roles[RolePosY] = "rolePosY";
  roles[RoleWidth] = "roleWidth";
  roles[RoleHeight] = "roleHeight";
  roles[RoleLayer] = "roleLayer";
  roles[RoleAcceptedButtons] = "roleAcceptedButtons";
  return roles;
}

Qt::ItemFlags EntitiesModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable;
}

QVariant EntitiesModel::headerData(int, Qt::Orientation, int) const {
  return QVariant();
}

QModelIndex EntitiesModel::index(int row, int column,
                                 const QModelIndex &) const {
  return this->createIndex(
      row, column,
      entityWrappersPtr->operator[](static_cast<std::size_t>(row)).get());
}

QModelIndex EntitiesModel::parent(const QModelIndex &) const {
  return QModelIndex();
}

int EntitiesModel::columnCount(const QModelIndex &) const { return 0; }

int EntitiesModel::rowCount(const QModelIndex &) const {
  return static_cast<int>(entityWrappersPtr->size());
}

QVariant EntitiesModel::data(const QModelIndex &index, int role) const {
  const auto &entityWrapper =
      entityWrappersPtr->operator[](static_cast<std::size_t>(index.row()));
  switch (role) {
  case RolePosX:
    return static_cast<int>(entityWrapper->getPosX());
  case RolePosY:
    return static_cast<int>(entityWrapper->getPosY());
  case RoleWidth:
    return static_cast<int>(entityWrapper->getWidth());
  case RoleHeight:
    return static_cast<int>(entityWrapper->getHeight());
  case RoleLayer:
    return entityWrapper->getLayer();
  case RoleAcceptedButtons: {
    unsigned int acceptedButtons = Qt::NoButton;
    if (entityWrapper->isSelectable()) {
      acceptedButtons |= Qt::LeftButton;
    }
    if (entityWrapper->isTargetable()) {
      acceptedButtons |= Qt::RightButton;
    }
    return acceptedButtons;
  }
  default:
    return QVariant();
  }
}

void EntitiesModel::entityChanged(const uuids::uuid &uuid) {
  const auto &index = this->uuidToIndexMap[uuid];
  this->dataChanged(index, index);
}
} // namespace ui
} // namespace how
