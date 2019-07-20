#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include "../entities/interactiveentity.h"
#include "./entitiesmanager.h"

namespace how {
namespace model {
class SelectionManager {
public:
  using army_selected_signal_t = ::boost::signals2::signal<void(Army *)>;
  using tile_selected_signal_t = ::boost::signals2::signal<void(Tile *)>;

public:
  SelectionManager(EntitiesManager &entitiesManager);

public:
  void selectByPosition(const types::point_t &position);
  InteractiveEntity *getSelection() const;
  bool hasSelection() const;
  void clearSelection();

private:
  void setSelection(InteractiveEntity *newSelection);

public:
  army_selected_signal_t armySelectedSignal;
  tile_selected_signal_t tileSelectedSignal;

private:
  EntitiesManager &entitiesManager;
  InteractiveEntity *selection;
};
} // namespace model
} // namespace how

#endif // SELECTIONMANAGER_H
