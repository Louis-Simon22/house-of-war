#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include "../entities/interactiveentity.h"

namespace how {
namespace model {
class SelectionManager {
public:
  SelectionManager();

public:
  void setSelection(InteractiveEntity *newSelection);
  InteractiveEntity *getSelection() const;
  bool hasSelection() const;
  void clearSelection();

private:
  InteractiveEntity *selection;
};
} // namespace model
} // namespace how

#endif // SELECTIONMANAGER_H
