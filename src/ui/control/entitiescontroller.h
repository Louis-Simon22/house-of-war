#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <QMouseEvent>
#include <QObject>

#include "../../model/managers/modelmanager.h"
#include "../bindings/armybindings.h"
#include "../bindings/voronoicellbindings.h"

namespace how {
namespace ui {
class EntitiesController : public QObject {
  Q_OBJECT

  Q_PROPERTY(ArmyBindings *armyBindings READ getArmyBindings CONSTANT)
  Q_PROPERTY(VoronoiCellBindings *voronoiCellBindings READ
                 getVoronoiCellBindings CONSTANT)

public:
  EntitiesController(model::ModelManager &modelManager);

public slots:
  void interactiveItemMouseEvent(QMouseEvent *event,
                                 InteractiveEntityItem *interactiveItem);
  void generateMapItems(QQuickItem *parent);

public:
  void onGraphEntitySelected(model::InteractiveEntity *interactiveEntity);
  void onGraphEntityTargeted(model::InteractiveEntity *interactiveEntity);

private:
  ArmyBindings *getArmyBindings();
  VoronoiCellBindings *getVoronoiCellBindings();

private:
  model::ModelManager &modelManager;
  const model::EntitiesManager *entitiesManager;
  SelectionManager selectionManager;
  ArmyBindings armyBindings;
  VoronoiCellBindings voronoiCellBindings;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
