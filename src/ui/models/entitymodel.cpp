#include "entitymodel.h"

#include <iostream>

namespace how {
namespace ui {
EntityModel::EntityModel() : QAbstractListModel(), uuidToIndexMap() {}

EntityModel::~EntityModel() {}

void EntityModel::entityChanged(boost::uuids::uuid uuid) {
  const auto &index = this->uuidToIndexMap[uuid];
  this->dataChanged(index, index);
}
} // namespace ui
} // namespace how
