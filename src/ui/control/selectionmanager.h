#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <QObject>

#include "../wrappers/selectableentitywrapper.h"

namespace how {
namespace ui {
class SelectionManager : public QObject {
  Q_OBJECT

public:
  SelectionManager();

public:
  bool hasSelection() const;
  void clearSelection();

private:
  void selectEntity(SelectableEntityWrapper *selectableEntityWrapper);

private:
  SelectableEntityWrapper *selection;
};
} // namespace ui
} // namespace how

#endif // SELECTIONMANAGER_H
