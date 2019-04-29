#include "army.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

Army::Army(types::point_t initialPosition,
           types::graph_vertex_desc_t currentVertexIndex)
    : GraphEntity(initialPosition, currentVertexIndex) {}

Army::~Army() {}

void Army::onIteration(float deltaTime) {
  auto minPoint = this->getPosition();
  auto maxPoint = this->getPosition();
  bg::subtract_value(minPoint, this->influenceAreaWidth / 2);
  bg::add_value(maxPoint, this->influenceAreaWidth / 2);
  const auto area = types::box_t(minPoint, maxPoint);
  // TODO maybe a one point polygon works for character?
}

} // namespace model
} // namespace how
