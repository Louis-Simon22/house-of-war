#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include "../entities/characters/army.h"
#include "../entities/terrain/tile.h"

namespace how {
namespace model {
class SelectionManager {
public:
  using army_selected_signal_t = ::nod::signal<void(Army *)>;
  using tile_selected_signal_t = ::nod::signal<void(Tile *)>;
  using multi_selection_signal_t = ::nod::signal<void()>;

public:
  SelectionManager();

public:
  InteractiveEntity *getSelection() const;
  std::vector<InteractiveEntity *> getSelections() const;
  bool hasSelection() const;
  void clearSelection();
  void addTileSelection(Tile *tileSelection);
  void addArmySelection(Army *armySelection);

private:
  void addSelection(InteractiveEntity *selection);

public:
  army_selected_signal_t armySelectedSignal;
  tile_selected_signal_t tileSelectedSignal;
  multi_selection_signal_t multiSelectionSignal;

private:
  std::vector<InteractiveEntity *> selections;
};
} // namespace model
} // namespace how

#endif // SELECTIONMANAGER_H
