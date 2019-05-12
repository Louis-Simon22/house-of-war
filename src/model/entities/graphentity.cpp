#include "graphentity.h"

#include <boost/uuid/uuid_generators.hpp>

namespace how {
namespace model {

GraphEntity::GraphEntity()
    : uuid(uuids::random_generator()()), layer(DEFAULT_LAYER),
      physicalChangSignal(), visualChangeSignal() {}

GraphEntity::GraphEntity(types::layer_t layer)
    : uuid(uuids::random_generator()()), layer(layer), physicalChangSignal(),
      visualChangeSignal() {}

GraphEntity::~GraphEntity() {}

const uuids::uuid &GraphEntity::getUuid() const { return this->uuid; }

types::layer_t GraphEntity::getLayer() const { return this->layer; }

types::point_t GraphEntity::getPosition() const {
  return types::point_t(this->getPosX(), this->getPosY());
}

} // namespace model
} // namespace how
