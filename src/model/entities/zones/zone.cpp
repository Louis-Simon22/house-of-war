#include "zone.h"

#include <boost/geometry/algorithms/convert.hpp>

namespace how {
namespace model {

Zone::Zone(const Entity *parentEntity) : Entity(parentEntity) {}

Zone::~Zone() {}

} // namespace model
} // namespace how
