#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <memory>
#include <vector>

#include <QObject>
#include <QQuickItem>

#include "../../model/managers/modelmanager.h"
#include "../painters/entitypainter.h"
#include "./graphentitycontroller.h"
#include "./modelthreadmanager.h"

namespace how {
namespace ui {
class MainController : public QObject {
  Q_OBJECT

  Q_PROPERTY(GraphEntityController *graphEntityController READ
                 getGraphEntityController NOTIFY newModelGenerated FINAL)

public:
  MainController();

signals:
  void newModelGenerated();

public slots:
  void newModel(int width, int height, float minimumVoronoiCellDistance,
                int randomSeed);
  void instantiateUiElements(QQuickItem *parent);

private:
  GraphEntityController *getGraphEntityController();
  void bindClickSignalAndSetObjectOwnership(EntityPainter* entityPainter);

private:
  model::ModelManager modelManager;
  ModelThreadManager modelThreadManager;
  std::unique_ptr<GraphEntityController> graphEntityControllerPtr;
};
} // namespace ui
} // namespace how
#endif // MODELCONTROLLER_H
