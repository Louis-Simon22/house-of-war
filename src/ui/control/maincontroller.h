#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <memory>
#include <vector>

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../entities/graphentityitem.h"
#include "./graphentitycontroller.h"
#include "./iterationtimermanager.h"
#include "./modelcontroller.h"
#include "./modelthreadmanager.h"

namespace how {
namespace ui {
class MainController : public QObject {
  Q_OBJECT

  Q_PROPERTY(ModelController *modelController READ getModelController CONSTANT)

public:
  MainController();

public slots:
  void generateMapItems(QQuickItem *parent);

private:
  ModelController *getModelController();
  void bindGraphEntityItemClickSignalAndSetObjectOwnership(
      GraphEntityItem *graphEntityItem);

private:
  ModelThreadManager *modelThreadManager;
  IterationTimerManager* iterationTimerManager;
  ModelController* modelController;
};
} // namespace ui
} // namespace how
#endif // MAINCONTROLLER_H
