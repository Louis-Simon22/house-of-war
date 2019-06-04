#include "modelthreadmanager.h"

#include <iostream>

namespace how {
namespace ui {

ModelThreadManager::ModelThreadManager(QObject *parent) : QObject(parent) {
  this->modelWorkerThread.start(QThread::HighPriority);
}

ModelThreadManager::~ModelThreadManager() {
  this->modelWorkerThread.quit();
  this->modelWorkerThread.wait();
}

void ModelThreadManager::registerQObjectOnThread(QObject *qObject) {
  qObject->moveToThread(&this->modelWorkerThread);
}

} // namespace ui
} // namespace how
