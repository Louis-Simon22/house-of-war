#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "./entitiescontroller.h"

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
  void iterateModel();
  void entitiesMouseEvent(int x, int y, int button);

public:
  EntitiesController *getEntitiesController();

private:
  QRect getWorldBounds() const;
  ModelController *getModelController();

private:
  model::ModelManager modelManager;
  EntitiesController entitiesController;
};
} // namespace ui
} // namespace how

#endif // MODELCONTROLLER_H
