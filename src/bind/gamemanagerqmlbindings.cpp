#include "gamemanagerqmlbindings.h"
#include <iostream>

namespace how {
namespace bind {
GameManagerQMLBindings::GameManagerQMLBindings(QObject* parent) {
  this->gameManagerPtr = std::make_unique<GameManager>();
}

void GameManagerQMLBindings::generateNewWorld(int width, int height) {
  auto config = ::how::model::types::WorldGenerationConfig();
  std::cout << width << std::endl;
  std::cout << height << std::endl;
  config.minCornerX = 0;
  config.minCornerY = 0;
  config.maxCornerX = width;
  config.maxCornerY = height;
  this->gameManagerPtr->generateNewWorld(config);
}

::how::bind::models::WorldModel* GameManagerQMLBindings::getWorldModel() const {
  auto* worldModel =
      new models::WorldModel(this->gameManagerPtr->getPointsList());
  QQmlEngine::setObjectOwnership(
      worldModel, QQmlEngine::ObjectOwnership::JavaScriptOwnership);
  return worldModel;
}

const QRect GameManagerQMLBindings::getWorldDimensions() const {
  const auto& bounds = this->gameManagerPtr->getWorldBounds();
  return QRect(
      bg::get<bg::min_corner, 0>(bounds), bg::get<bg::min_corner, 1>(bounds),
      bg::get<bg::max_corner, 0>(bounds), bg::get<bg::max_corner, 1>(bounds));
}
}  // namespace bind
}  // namespace how
