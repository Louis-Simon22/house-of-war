#include "graphentity.h"

#include <boost/uuid/uuid_generators.hpp>

namespace how {
namespace model {

GraphEntity::GraphEntity() : GraphEntity(DEFAULT_LAYER) {}

GraphEntity::GraphEntity(types::layer_t layer)
    : uuid(uuids::random_generator()()), layer(layer),
      dimensionsChangedSignal(), visualChangedSignal(), destructionSignal() {}

GraphEntity::~GraphEntity() { destructionSignal(); }

const uuids::uuid &GraphEntity::getUuid() const { return this->uuid; }

types::layer_t GraphEntity::getLayer() const { return this->layer; }

bool GraphEntity::isSelected() const { return this->selected; }

void GraphEntity::setSelected(bool selected) {
  this->selected = selected;
  this->visualChangedSignal();
}

types::point_t GraphEntity::getPosition() const {
  return types::point_t(this->getPosX(), this->getPosY());
}

} // namespace model
} // namespace how
