#ifndef ITERATIONTIMERMANAGER_H
#define ITERATIONTIMERMANAGER_H

#include <QObject>
#include <QTimer>

namespace how {
namespace ui {
class IterationTimerManager : public QObject {
  Q_OBJECT

public:
  IterationTimerManager(QObject *parent = nullptr);
  ~IterationTimerManager();

public slots:
  void toggleIterations();
  void pauseIterations();
  void resumeIterations();
  void setIterationInterval(int msec);

signals:
  void iterate();

private:
  QTimer modelIterationTimer;
};
} // namespace ui
} // namespace how

#endif // ITERATIONTIMERMANAGER_H
