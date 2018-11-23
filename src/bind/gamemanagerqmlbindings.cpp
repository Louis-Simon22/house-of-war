#include "gamemanagerqmlbindings.h"

namespace how {
namespace bind {
GameManagerQMLBindings::GameManagerQMLBindings(QObject* parent) {
  this->worldModelPtr = std::make_unique<models::WorldModel>();
}

void GameManagerQMLBindings::generateNewWorld(
    ::how::model::types::WorldGenerationConfig config) {
  this->gameManagerPtr->generateNewWorld(config);
}

const models::WorldModel* GameManagerQMLBindings::getWorldModel() const {
  return this->worldModelPtr.get();
}

const QRect GameManagerQMLBindings::getWorldDimensions() const {
  const auto& bounds = this->gameManagerPtr->getWorldBounds();
  return QRect(
      bg::get<bg::min_corner, 0>(bounds), bg::get<bg::min_corner, 1>(bounds),
      bg::get<bg::max_corner, 0>(bounds), bg::get<bg::max_corner, 1>(bounds));
}
}  // namespace bind
}  // namespace how
