#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <QObject>

#include "../../model/entities/interactiveentity.h"

namespace how {
namespace ui {
class SelectionManager : public QObject {
  Q_OBJECT

public:
  SelectionManager();

public:
  void setSelection(model::InteractiveEntity *newSelection);
  model::InteractiveEntity *getSelection() const;
  bool hasSelection() const;
  void clearSelection();

private:
  model::InteractiveEntity *selection;
};
} // namespace ui
} // namespace how

#endif // SELECTIONMANAGER_H
