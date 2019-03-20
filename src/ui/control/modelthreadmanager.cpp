#include "modelthreadmanager.h"

#include <iostream>

namespace how {
namespace ui {
ModelThreadManager::ModelThreadManager()
    : movementManagerPtr(std::make_unique<model::MovementManager>()) {
  this->modelWorkerThread.start(QThread::HighPriority);
  connect(&this->modelIterationTimer, &QTimer::timeout, this,
          &ModelThreadManager::workerThreadIteration);
  std::cout << "Model operations thread " << this->modelWorkerThread.thread()
            << std::endl;
}

ModelThreadManager::~ModelThreadManager() {
  this->modelWorkerThread.quit();
  this->modelWorkerThread.wait();
}

void ModelThreadManager::pauseIterations() { this->modelIterationTimer.stop(); }

void ModelThreadManager::resumeIterations() {
  this->modelIterationTimer.start();
}

void ModelThreadManager::setIterationInterval(int msec) {
  this->modelIterationTimer.setInterval(msec);
}

void ModelThreadManager::workerThreadIteration() {
  this->movementManagerPtr->progressAll(this->modelIterationTimer.interval());
}
} // namespace ui
} // namespace how
