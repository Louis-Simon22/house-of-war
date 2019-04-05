#ifndef MODELTHREADMANAGER_H
#define MODELTHREADMANAGER_H

#include <QThread>
#include <QTimer>
#include <memory>

#include "../../model/entities/movement/movementmanager.h"
#include "../wrappers/worlddataqmlwrapper.h"

namespace how {
namespace ui {
class ModelThreadManager : public QObject {
  Q_OBJECT

public:
  ModelThreadManager();
  ~ModelThreadManager();

public:
  void registerQObjectOnThread(QObject* qObject);

public slots:
  void pauseIterations();
  void resumeIterations();
  void setIterationInterval(int msec);

signals:
  void workerThreadIteration();

private:
  QTimer modelIterationTimer;
  QThread modelWorkerThread;
};
} // namespace ui
} // namespace how

#endif // MODELTHREADMANAGER_H
