#include "entitymodel.h"

namespace how {
namespace ui {
EntityModel::EntityModel() : QAbstractListModel(), uuidToIndexMap() {}

EntityModel::~EntityModel() {}

void EntityModel::entityChanged(const uuids::uuid& uuid) {
  const auto &index = this->uuidToIndexMap[uuid];
  this->dataChanged(index, index);
}
} // namespace ui
} // namespace how
