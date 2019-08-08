#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QList>
#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../threading/iterationtimermanager.h"
#include "./controlmodewrapper.h"
#include "./entitiescontroller.h"

namespace how {
namespace ui {
class ModelController : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      QRect worldBounds READ getWorldBounds NOTIFY newModelGenerated FINAL)
  Q_PROPERTY(EntitiesController *entitiesController READ getEntitiesController
                 CONSTANT FINAL)
  Q_PROPERTY(IterationTimerManager *iterationTimerManager READ
                 getIterationTimerManager CONSTANT FINAL)
  Q_PROPERTY(int controlMode READ getControlMode WRITE setControlMode NOTIFY
                 controlModeChanged FINAL)

public:
  ModelController(QObject *parent = nullptr);

signals:
  void newModelGenerated();
  void controlModeChanged(int controlMode);

public slots:
  void newModel(QString fileName, int width, int height,
                float minimumVoronoiCellDistance, int randomSeed);
  void saveToFile();
  void loadFromFile(QString name);
  void entitiesMouseEvent(int x, int y, int button);

public:
  Q_INVOKABLE QList<QObject *> getAllSaveFiles();

private slots:
  void iterateModel();

public:
  EntitiesController *getEntitiesController();

private:
  QRect getWorldBounds() const;
  ModelController *getModelController();
  IterationTimerManager *getIterationTimerManager();
  int getControlMode() const;
  void setControlMode(int controlMode);

private:
  model::ModelManager modelManager;
  EntitiesController entitiesController;
  IterationTimerManager iterationTimerManager;
  ControlModeWrapper::ControlMode currentControlMode;
};
} // namespace ui
} // namespace how

#endif // MODELCONTROLLER_H
