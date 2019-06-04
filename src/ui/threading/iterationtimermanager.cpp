#include "iterationtimermanager.h"

namespace how {
namespace ui {

IterationTimerManager::IterationTimerManager(QObject *parent)
    : QObject(parent) {
  this->modelIterationTimer.setInterval(350);
  connect(&this->modelIterationTimer, &QTimer::timeout, this,
          &IterationTimerManager::iterate, Qt::QueuedConnection);
}

IterationTimerManager::~IterationTimerManager() {}

void IterationTimerManager::pauseIterations() {
  this->modelIterationTimer.stop();
}

void IterationTimerManager::resumeIterations() {
  this->modelIterationTimer.start();
}

void IterationTimerManager::setIterationInterval(int msec) {
  this->modelIterationTimer.setInterval(msec);
}
} // namespace ui
} // namespace how
