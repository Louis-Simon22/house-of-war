#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <QObject>

#include "../wrappers/entitywrapper.h"

namespace how {
namespace ui {
class SelectionManager : public QObject {
  Q_OBJECT

public:
  SelectionManager();

public:
  void selectEntity(EntityWrapper *newSelection);
  EntityWrapper *getSelection() const;
  bool hasSelection() const;
  void clearSelection();

private:
  EntityWrapper *selection;
};
} // namespace ui
} // namespace how

#endif // SELECTIONMANAGER_H
