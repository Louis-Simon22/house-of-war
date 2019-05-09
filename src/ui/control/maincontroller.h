#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <vector>

#include <QObject>

#include "../../model/managers/modelmanager.h"
#include "../models/entitiesmodel.h"
#include "../wrappers/entitywrapper.h"
#include "../wrappers/modelmanagerwrapper.h"
#include "./graphentitycontroller.h"
#include "./modelthreadmanager.h"

namespace how {
namespace ui {
class MainController : QObject {
  Q_OBJECT

  Q_PROPERTY(GraphEntityController *graphEntityController READ
                 getGraphEntityController NOTIFY newModelGenerated FINAL)
  Q_PROPERTY(EntitiesModel *entitiesModel READ getEntitiesModel NOTIFY
                 newModelGenerated FINAL)
  Q_PROPERTY(ModelManagerWrapper *modelManagerWrapper READ getModelManagerWrapper
                 NOTIFY newModelGenerated FINAL)

public:
  MainController();

public:
  void instantiateEntityWrappers();

public:
  GraphEntityController *getGraphEntityController();
  EntitiesModel *getEntitiesModel();
  ModelManagerWrapper *getModelManagerWrapper();

private:
  model::ModelManager modelManager;
  ModelThreadManager modelThreadManager;
  std::vector<std::unique_ptr<EntityWrapper>> entityWrappers;
};
} // namespace ui
} // namespace how
#endif // MODELCONTROLLER_H
