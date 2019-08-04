#ifndef MODELEVENT_H
#define MODELEVENT_H

#include "../managers/entitiesmanager.h"
#include "../managers/selectionmanager.h"

namespace how {
namespace model {
class ModelEvent {
public:
  ModelEvent();

public:
  virtual ~ModelEvent() = 0;

public:
  virtual void applyEvent(EntitiesManager &entitiesManager,
                          SelectionManager &selectionManager) const = 0;
};
} // namespace model
} // namespace how

#endif // MODELEVENT_H
