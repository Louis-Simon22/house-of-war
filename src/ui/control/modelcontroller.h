#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QList>
#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../threading/iterationtimermanager.h"
#include "./entitiescontroller.h"

namespace how {
namespace ui {
class ModelController : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      QRect worldBounds READ getWorldBounds NOTIFY newModelGenerated FINAL)
  Q_PROPERTY(EntitiesController *entitiesController READ getEntitiesController
                 CONSTANT FINAL)

public:
  ModelController(QObject *parent = nullptr);

signals:
  void newModelGenerated();

public slots:
  void newModel(int width, int height, float minimumVoronoiCellDistance,
                int randomSeed);
  void saveToFile(QString name);
  void loadFromFile(QString name);
  void entitiesMouseEvent(int x, int y, int button, int controlMode);

public:
  Q_INVOKABLE QList<QObject *> getAllSaveFiles();

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
