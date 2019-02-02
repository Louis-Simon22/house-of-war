#include "gamemanagerqmlbindings.h"

namespace how {
namespace bind {
GameManagerQMLBindings::GameManagerQMLBindings(QObject *) {
  this->gameManagerPtr = std::make_unique<GameManager>();
}

void GameManagerQMLBindings::generateNewWorld(int width, int height) {
  auto config = ::how::model::types::WorldGenerationConfig();
  config.minCornerX = 0;
  config.minCornerY = 0;
  config.maxCornerX = width;
  config.maxCornerY = height;
  this->gameManagerPtr->generateNewWorld(config);
}

WorldModel *GameManagerQMLBindings::getWorldModel() const {
  auto *worldModel = new WorldModel(this->gameManagerPtr->getCellCentroids());
  QQmlEngine::setObjectOwnership(
      worldModel, QQmlEngine::ObjectOwnership::JavaScriptOwnership);
  return worldModel;
}

const QList<QVariant> GameManagerQMLBindings::getOutlineSegments() const {
    return convert(this->gameManagerPtr->getUniqueVoronoiSegments());
}

const QList<QVariant> GameManagerQMLBindings::getPathSegments() const {
    return convert(this->gameManagerPtr->getUniqueDelaunaySegments());
}

const QRect GameManagerQMLBindings::getWorldBounds() const {
  const auto* bounds = this->gameManagerPtr->getWorldBounds();
  return QRect(
      bg::get<bg::min_corner, 0>(bounds), bg::get<bg::min_corner, 1>(bounds),
              bg::get<bg::max_corner, 0>(bounds), bg::get<bg::max_corner, 1>(bounds));
}

const QList<QVariant> GameManagerQMLBindings::convert(const std::vector<model::types::segment_t>* segments) const
{
    auto convertedSegments = QList<QVariant>();

    for (auto outlineSegment : *segments) {
        const auto &p1 =
                QPoint(bg::get<0, 0>(outlineSegment), bg::get<0, 1>(outlineSegment));
        const auto &p2 =
                QPoint(bg::get<1, 0>(outlineSegment), bg::get<1, 1>(outlineSegment));
        convertedSegments.insert(convertedSegments.size(),
                                 QList<QVariant>({p1, p2}));
    }

    return convertedSegments;
}
} // namespace bind
} // namespace how
