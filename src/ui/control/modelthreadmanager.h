#ifndef MODELTHREADMANAGER_H
#define MODELTHREADMANAGER_H

#include <QThread>
#include <QTimer>
#include <memory>

#include "../wrappers/worlddataqmlwrapper.h"
#include "../../model/entities/movement/movementmanager.h"

namespace how {
namespace ui {
class ModelThreadManager : public QObject {
  Q_OBJECT

public:
  ModelThreadManager();
  ~ModelThreadManager();

public slots:
  void pauseIterations();
  void resumeIterations();
  void setIterationInterval(int msec);
  void workerThreadIteration();

private:
  QTimer modelIterationTimer;
  QThread modelWorkerThread;
  std::unique_ptr<model::MovementManager> movementManagerPtr;
};
} // namespace ui
} // namespace how

#endif // MODELTHREADMANAGER_H
