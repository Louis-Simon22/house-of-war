#ifndef MODELTHREADMANAGER_H
#define MODELTHREADMANAGER_H

#include <QThread>
#include <QTimer>
#include <memory>

namespace how {
namespace ui {
class ModelThreadManager : public QObject {
  Q_OBJECT

public:
  ModelThreadManager(QObject *parent);
  ~ModelThreadManager();

public:
  void registerQObjectOnThread(QObject *qObject);

private:
  QThread modelWorkerThread;
};
} // namespace ui
} // namespace how

#endif // MODELTHREADMANAGER_H
