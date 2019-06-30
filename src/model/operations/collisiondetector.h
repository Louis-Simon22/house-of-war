#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <vector>

namespace how {
namespace model {

template <typename CollidableItems, typename CollisionDetector>
std::vector<CollidableItems>
getCollisions(const std::vector<CollidableItems> &items,
              CollisionDetector collisionDetector) {
  auto collidedItems = std::vector<CollidableItems>();

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
