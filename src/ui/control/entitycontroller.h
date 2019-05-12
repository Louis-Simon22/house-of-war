#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <memory>

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/entitychangemanager.h"
#include "../../model/managers/graphentitymanager.h"
#include "../../model/managers/worldmanager.h"
#include "../models/entitiesmodel.h"
#include "../wrappers/entitywrapper.h"
#include "../wrappers/worldmanagerwrapper.h"
#include "./selectionmanager.h"

namespace how {
namespace ui {
class EntityController : public QObject {
  Q_OBJECT

public:
  EntityController(
      model::EntityChangeManager *entityChangeManagerPtr,
      std::vector<std::unique_ptr<EntityWrapper>> *entityWrappersPtr);

public slots:
  void iterateAllChanges(float deltaTime);

public:
  Q_INVOKABLE QQuickItem *createEntityWrapperPainterAtIndex(int index);
  Q_INVOKABLE void onEntityWrapperClicked(int entityWrapperIndexInt,
                                          int mouseButton);

private:
  void moveEntityTo(EntityWrapper *selection, EntityWrapper *target);

private:
  SelectionManager selectionManager;
  model::EntityChangeManager *entityChangeManagerPtr;
  std::vector<std::unique_ptr<EntityWrapper>> *entityWrappersPtr;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
