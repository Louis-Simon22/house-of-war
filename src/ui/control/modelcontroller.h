#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>

#include "../../model/managers/graphentitymanager.h"
#include "../../model/managers/modelmanager.h"
#include "./graphentitycontroller.h"

namespace how {
namespace ui {
class ModelController : public QObject {
  Q_OBJECT

  Q_PROPERTY(GraphEntityController *graphEntityController READ
                 getGraphEntityControllerPtr NOTIFY newModelGenerated FINAL)

public:
  ModelController(QObject *parent = nullptr);

signals:
  void newModelGenerated();

public slots:
  void newModel(int width, int height, float minimumVoronoiCellDistance,
                int randomSeed);
  void iterateModel();

public:
  model::GraphEntityManager *getGraphEntityManagerPtr();
  GraphEntityController *getGraphEntityControllerPtr();

private:
  model::ModelManager modelManager;
  std::unique_ptr<GraphEntityController> graphEntityControllerPtr;
};
} // namespace ui
} // namespace how

#endif // MODELCONTROLLER_H
