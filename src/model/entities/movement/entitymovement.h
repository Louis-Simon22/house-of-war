#ifndef ENTITYMOVEMENT_H
#define ENTITYMOVEMENT_H

namespace how {
namespace model {
class EntityMovement {
public:
  EntityMovement();
  virtual ~EntityMovement() = 0;

public:
  virtual bool progress(float deltaTime) = 0;
  virtual void destinationReached() = 0;
};
} // namespace model
} // namespace how

#endif // ENTITYMOVEMENT_H
