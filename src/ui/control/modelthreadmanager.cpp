#include "modelthreadmanager.h"

#include <iostream>

namespace how {
namespace ui {
ModelThreadManager::ModelThreadManager() : QObject(nullptr) {
  this->modelWorkerThread.start(QThread::HighPriority);
  this->modelIterationTimer.setInterval(400);
  connect(&this->modelIterationTimer, &QTimer::timeout, this,
          &ModelThreadManager::workerThreadIteration);
  std::cout << "Model operations thread " << this->modelWorkerThread.thread()
            << std::endl;
}

ModelThreadManager::~ModelThreadManager() {
  this->modelWorkerThread.quit();
  this->modelWorkerThread.wait();
}

void ModelThreadManager::registerQObjectOnThread(QObject *qObject) {
  qObject->moveToThread(&this->modelWorkerThread);
}

void ModelThreadManager::pauseIterations() { this->modelIterationTimer.stop(); }

void ModelThreadManager::resumeIterations() {
  this->modelIterationTimer.start();
}

void ModelThreadManager::setIterationInterval(int msec) {
  this->modelIterationTimer.setInterval(msec);
}

void ModelThreadManager::workerThreadIteration() {
  this->iteration(this->modelIterationTimer.interval());
}
} // namespace ui
} // namespace how
