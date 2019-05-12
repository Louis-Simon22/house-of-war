#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <memory>

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/graphentitymanager.h"
#include "./selectionmanager.h"

namespace how {
namespace ui {
class EntityController : public QObject {
  Q_OBJECT

public:
  EntityController(model::GraphEntityManager &graphEntityManager);

public slots:
  void iterateAllChanges(float deltaTime);

private:
  void moveEntityTo(model::GraphEntity &selection, model::GraphEntity &target);

private:
  SelectionManager selectionManager;
  model::GraphEntityManager &graphEntityManager;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
