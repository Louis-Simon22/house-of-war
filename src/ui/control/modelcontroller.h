#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../items/interactiveentityitem.h"
#include "./entitiescontroller.h"

// TODO all modifications come through this class
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
  void generateMapItems(QQuickItem *parent);

private:
  void bindEntityItemClickSignalAndSetObjectOwnership(
      InteractiveEntityItem *interactiveEntityItem);

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
