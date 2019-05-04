#ifndef GAMEDATAMANAGERQMLWRAPPER_H
#define GAMEDATAMANAGERQMLWRAPPER_H

#include <QObject>
#include <QQuickItem>
#include <QRect>

#include "../../model/managers/modelmanager.h"
#include "../control/graphentitycontroller.h"
#include "../control/modelthreadmanager.h"
#include "../models/entitiesmodel.h"
#include "./entitywrapper.h"

namespace how {
namespace ui {
class ModelManagerWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      QRect worldBounds READ getWorldBounds NOTIFY newModelGenerated FINAL)
  Q_PROPERTY(GraphEntityController *graphEntityController READ
                 getGraphEntityController NOTIFY newModelGenerated FINAL)
  Q_PROPERTY(EntitiesModel *entitiesModel READ getEntitiesModel NOTIFY
                 newModelGenerated FINAL)

public:
  ModelManagerWrapper(QObject *parent = nullptr);

signals:
  void newModelGenerated();

public slots:
  void newModel(int width, int height, float minimumVoronoiCellDistance,
                int randomSeed);
  void instantiateEntityWrappers();

private:
  GraphEntityController *getGraphEntityController();
  EntitiesModel *getEntitiesModel();
  QRect getWorldBounds() const;

private:
  model::ModelManager modelManager;
  ModelThreadManager modelThreadManager;
  std::vector<std::unique_ptr<EntityWrapper>> entityWrappers;
};
} // namespace ui
} // namespace how

#endif // GAMEDATAMANAGERQMLBINDINGS_H
