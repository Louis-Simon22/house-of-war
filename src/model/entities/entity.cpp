#include "entity.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
} // namespace

Entity::Entity(const Entity *parent)
    : Entity(parent->getLayer(), types::point_t(), parent) {}

Entity::Entity(types::layer_t layer, const Entity *parent)
    : Entity(layer, types::point_t(), parent) {}

Entity::Entity(types::layer_t layer, types::point_t position,
               const Entity *parent)
    : changedSignal(), parent(parent), layer(layer), position(position) {}

Entity::~Entity() {}

types::layer_t Entity::getLayer() const { return this->layer; }

const types::point_t &Entity::getPosition() const { return this->position; }

types::coordinate_t Entity::getPosX() const {
  return bg::get<0>(this->position);
}

types::coordinate_t Entity::getPosY() const {
  return bg::get<1>(this->position);
}

types::coordinate_t Entity::getAbsolutePosX() const {
  return bg::get<0>(this->position) +
         (this->parent ? this->parent->getAbsolutePosX() : 0);
}

types::coordinate_t Entity::getAbsolutePosY() const {
  return bg::get<1>(this->position) +
         (this->parent ? this->parent->getAbsolutePosY() : 0);
}

types::point_t Entity::getAbsolutePosition() const {
  return types::point_t(this->getAbsolutePosX(), this->getAbsolutePosY());
}

void Entity::setPosition(const types::point_t &position) {
  // TODO move the entities in the spatial index
  bg::set<0>(this->position, bg::get<0>(position));
  bg::set<1>(this->position, bg::get<1>(position));
  this->changedSignal();
}
} // namespace model
} // namespace how
