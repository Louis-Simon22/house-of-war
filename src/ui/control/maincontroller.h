#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <memory>
#include <vector>

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../painters/graphentitypainter.h"
#include "./graphentitycontroller.h"
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
  void generateMapElements(QQuickItem *parent);

private:
  ModelController *getModelController();
  void bindPainterClickSignalAndSetObjectOwnership(
      PainterItem *entityPainter);

private:
  ModelThreadManager modelThreadManager;
  ModelController modelController;
};
} // namespace ui
} // namespace how
#endif // MAINCONTROLLER_H
