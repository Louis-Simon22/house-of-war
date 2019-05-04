#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <memory>

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/entitychangemanager.h"
#include "../../model/managers/graphentitymanager.h"
#include "../../model/managers/worldmanager.h"
#include "../wrappers/entitywrapper.h"

namespace how {
namespace ui {
class GraphEntityController : public QObject {
  Q_OBJECT

public:
  GraphEntityController();
  GraphEntityController(
      model::EntityChangeManager *entityChangeManagerPtr,
      std::vector<std::unique_ptr<EntityWrapper>> *entityWrappers);

public slots:
  void iterateAllChanges(float deltaTime);

public:
  Q_INVOKABLE void addMoveOrder(int characterIndex, int voronoiCellIndex);
  Q_INVOKABLE QQuickItem *createEntityWrapperPainterAtIndex(int index);

private:
  model::EntityChangeManager *entityChangeManagerPtr;
  std::vector<std::unique_ptr<EntityWrapper>> *entityWrappersPtr;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
