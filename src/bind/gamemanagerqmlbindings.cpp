#include "gamemanagerqmlbindings.h"
#include <iostream>

namespace how {
namespace bind {
GameManagerQMLBindings::GameManagerQMLBindings(QObject *) {
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

WorldModel *GameManagerQMLBindings::getWorldModel() const {
  auto *worldModel = new WorldModel(this->gameManagerPtr->getPointsList());
  QQmlEngine::setObjectOwnership(
      worldModel, QQmlEngine::ObjectOwnership::JavaScriptOwnership);
  return worldModel;
}

const QList<QVariant> GameManagerQMLBindings::getOutlineSegments() const {
  auto convertedSegments = QList<QVariant>();
  const auto *outlineSegments = this->gameManagerPtr->getOutlineSegments();

  std::cout << "Get outline segments" << std::endl;
  std::cout << "===================" << std::endl;
  for (auto outlineSegment : *outlineSegments) {
    const auto &p1 =
        QPoint(bg::get<0, 0>(outlineSegment), bg::get<0, 1>(outlineSegment));
    const auto &p2 =
        QPoint(bg::get<1, 0>(outlineSegment), bg::get<1, 1>(outlineSegment));
    convertedSegments.insert(convertedSegments.size(),
                             QList<QVariant>({p1, p2}));
    std::cout << p1.x() << "," << p1.y() << "|" << p1.x() << "," << p2.y()
              << std::endl;
  }

  return convertedSegments;
}

const QRect GameManagerQMLBindings::getWorldBounds() const {
  const auto &bounds = this->gameManagerPtr->getWorldBounds();
  return QRect(
      bg::get<bg::min_corner, 0>(bounds), bg::get<bg::min_corner, 1>(bounds),
      bg::get<bg::max_corner, 0>(bounds), bg::get<bg::max_corner, 1>(bounds));
}
} // namespace bind
} // namespace how
