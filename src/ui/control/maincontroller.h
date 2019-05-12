#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <memory>
#include <vector>

#include <QObject>

#include "../../model/managers/modelmanager.h"
#include "../models/entitiesmodel.h"
#include "../wrappers/entitywrapper.h"
#include "../wrappers/worldmanagerwrapper.h"
#include "./armycontroller.h"
#include "./charactercontroller.h"
#include "./entitycontroller.h"
#include "./modelthreadmanager.h"

namespace how {
namespace ui {
class MainController : public QObject {
  Q_OBJECT

  Q_PROPERTY(EntityController *entityController READ getEntityController NOTIFY
                 newModelGenerated FINAL)
  Q_PROPERTY(EntitiesModel *entitiesModel READ getEntitiesModel NOTIFY
                 newModelGenerated FINAL)
  Q_PROPERTY(WorldManagerWrapper *worldManagerWrapper READ
                 getWorldManagerWrapper NOTIFY newModelGenerated FINAL)

public:
  MainController();

signals:
  void newModelGenerated();

public slots:
  void newModel(int width, int height, float minimumVoronoiCellDistance,
                int randomSeed);

private:
  void instantiateUiElements();

public:
  EntityController *getEntityController();
  EntitiesModel *getEntitiesModel();
  WorldManagerWrapper *getWorldManagerWrapper();

private:
  model::ModelManager modelManager;
  ModelThreadManager modelThreadManager;
  std::vector<std::unique_ptr<EntityWrapper>> entityWrappers;
  std::unique_ptr<EntityController> entityControllerPtr;
  std::unique_ptr<ArmyController> armyControllerPtr;
  std::unique_ptr<CharacterController> characterControllerPtr;
  std::unique_ptr<EntitiesModel> entitiesModelPtr;
  std::unique_ptr<WorldManagerWrapper> worldManagerWrapperPtr;
};
} // namespace ui
} // namespace how
#endif // MODELCONTROLLER_H
