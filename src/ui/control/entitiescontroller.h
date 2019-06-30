#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <QMouseEvent>
#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../bindings/armybindings.h"
#include "../bindings/tilebindings.h"

namespace how {
namespace ui {
class EntitiesController : public QObject {
  Q_OBJECT

  Q_PROPERTY(ArmyBindings *armyBindings READ getArmyBindings CONSTANT)
  Q_PROPERTY(
      TileBindings *tileBindings READ getTileBindings CONSTANT)

public:
  EntitiesController(model::ModelManager &modelManager);

public slots:
  void generateMapItems(QQuickItem *parent);

private:
  ArmyBindings *getArmyBindings();
  TileBindings *getTileBindings();

private:
  model::ModelManager &modelManager;
  const model::EntitiesManager *entitiesManager;
  ArmyBindings armyBindings;
  TileBindings tileBindings;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
