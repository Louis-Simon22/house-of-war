#include "graphentity.h"

#include <boost/uuid/uuid_generators.hpp>

namespace how {
namespace model {

GraphEntity::GraphEntity(types::layer_t layer, types::point_t position)
    : uuid(uuids::random_generator()()), layer(layer), position(position),
      changeSignals() {}

GraphEntity::~GraphEntity() { this->changeSignals.destructionSignal(); }

const uuids::uuid &GraphEntity::getUuid() const { return this->uuid; }

types::layer_t GraphEntity::getLayer() const { return this->layer; }

types::coordinate_t GraphEntity::getPosX() const {
  return bg::get<0>(this->position);
}

types::coordinate_t GraphEntity::getPosY() const {
  return bg::get<1>(this->position);
}

const types::point_t &GraphEntity::getPosition() const {
  return this->position;
}

void GraphEntity::setPosition(const types::point_t &position) {
  bg::set<0>(this->position, bg::get<0>(position));
  bg::set<1>(this->position, bg::get<1>(position));
  this->changeSignals.dimensionsChangedSignal();
}

bool GraphEntity::isSelected() const { return this->selected; }

void GraphEntity::setSelected(bool selected) {
  this->selected = selected;
  this->changeSignals.visualChangedSignal();
}

GraphEntity::ChangeSignals::ChangeSignals()
    : dimensionsChangedSignal(), visualChangedSignal(), destructionSignal() {}

GraphEntity::ChangeSignals::ChangeSignals(const GraphEntity::ChangeSignals &)
    : ChangeSignals() {}

GraphEntity::ChangeSignals &GraphEntity::ChangeSignals::
operator=(const GraphEntity::ChangeSignals &) {
  return *this;
}

} // namespace model
} // namespace how
