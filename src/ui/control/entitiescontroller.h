#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <QMouseEvent>
#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../bindings/armybindings.h"
#include "../bindings/tilebindings.h"
#include "./tilescontroller.h"

namespace how {
namespace ui {
class EntitiesController : public QObject {
  Q_OBJECT

  Q_PROPERTY(ArmyBindings *armyBindings READ getArmyBindings CONSTANT FINAL)
  Q_PROPERTY(TileBindings *tileBindings READ getTileBindings CONSTANT FINAL)
  Q_PROPERTY(
      TilesController *tilesController READ getTilesController CONSTANT FINAL)

public:
  EntitiesController(model::ModelManager &modelManager);

public slots:
  void generateMapItems(QQuickItem *parent);

private:
  ArmyBindings *getArmyBindings();
  TileBindings *getTileBindings();
  TilesController *getTilesController();

private:
  model::ModelManager &modelManager;
  const model::EntitiesManager *entitiesManager;
  ArmyBindings armyBindings;
  TileBindings tileBindings;
  TilesController tilesController;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
