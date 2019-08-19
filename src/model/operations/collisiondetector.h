#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <algorithm>
#include <vector>

namespace how {
namespace model {

template <typename CollidableItem, typename CollisionDetector>
std::vector<CollidableItem>
getCollisions(const std::vector<CollidableItem> &items,
              CollisionDetector collisionDetector) {
  auto collidedItems = std::vector<CollidableItem>();

  for (auto &item : items) {
    if (collisionDetector(item)) {
      collidedItems.push_back(item);
    }
  }

  return collidedItems;
}

} // namespace model
} // namespace how

#endif // COLLISIONDETECTOR_H
