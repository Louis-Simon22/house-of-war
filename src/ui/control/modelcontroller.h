#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "./entitiescontroller.h"
#include "../threading/iterationtimermanager.h"

namespace how {
namespace ui {
class ModelController : public QObject {
  Q_OBJECT

  Q_PROPERTY(QRect worldBounds READ getWorldBounds CONSTANT FINAL)
  Q_PROPERTY(EntitiesController *entitiesController READ getEntitiesController
                 CONSTANT)

public:
  ModelController(QObject *parent = nullptr);

signals:
  void newModelGenerated();

public slots:
  void newModel(int width, int height, float minimumVoronoiCellDistance,
                int randomSeed);
  void entitiesMouseEvent(int x, int y, int button);

private slots:
  void iterateModel();

public:
  EntitiesController *getEntitiesController();

private:
  QRect getWorldBounds() const;
  ModelController *getModelController();

private:
  model::ModelManager modelManager;
  EntitiesController entitiesController;
  IterationTimerManager iterationTimerManager;
};
} // namespace ui
} // namespace how

#endif // MODELCONTROLLER_H
