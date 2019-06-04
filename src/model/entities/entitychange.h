#ifndef ENTITY_CHANGE_H
#define ENTITY_CHANGE_H

namespace how {
namespace model {
class EntityChange {
public:
  EntityChange();
  virtual ~EntityChange();

public:
  virtual bool progress() = 0;
  virtual void destinationReached() = 0;
};
} // namespace model
} // namespace how

#endif // ENTITY_CHANGE_H
