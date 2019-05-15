#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <memory>
#include <vector>

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../painters/entitypainter.h"
#include "./entitycontroller.h"
#include "./modelthreadmanager.h"
#include "./worldcontroller.h"

namespace how {
namespace ui {
class MainController : public QObject {
  Q_OBJECT

  Q_PROPERTY(EntityController *entityController READ getEntityController NOTIFY
                 newModelGenerated FINAL)
  Q_PROPERTY(WorldController *worldController READ getWorldController
                 NOTIFY newModelGenerated FINAL)

public:
  MainController();

signals:
  void newModelGenerated();

public slots:
  void newModel(int width, int height, float minimumVoronoiCellDistance,
                int randomSeed);
  void instantiateUiElements(QQuickItem *parent);

private:
  void bindEntityPainter(QQuickItem *parent, EntityPainter *entityPainter);
  static QQuickItem *instantiateMouseAreaItem(QQuickItem *parent);

public:
  EntityController *getEntityController();
  WorldController *getWorldController();

private:
  model::ModelManager modelManager;
  ModelThreadManager modelThreadManager;
  std::unique_ptr<EntityController> entityControllerPtr;
  std::unique_ptr<WorldController> worldControllerPtr;
};
} // namespace ui
} // namespace how
#endif // MODELCONTROLLER_H
