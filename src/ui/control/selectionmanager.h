#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <QObject>

#include "../../model/entities/graphentity.h"

namespace how {
namespace ui {
class SelectionManager : public QObject {
  Q_OBJECT

public:
  SelectionManager();

public:
  void setSelection(model::GraphEntity *newSelection);
  model::GraphEntity *getSelection() const;
  bool hasSelection() const;
  void clearSelection();

private:
  model::GraphEntity *selection;
};
} // namespace ui
} // namespace how

#endif // SELECTIONMANAGER_H
