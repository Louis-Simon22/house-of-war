#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <QMouseEvent>
#include <QObject>

#include "../../model/managers/modelmanager.h"
#include "./selectionmanager.h"

namespace how {
namespace ui {
class EntitiesController : public QObject {
  Q_OBJECT

public:
  EntitiesController(model::ModelManager &modelManager);

public slots:
  void mousePressedOnGraphEntityPainter(QMouseEvent *event,
                                        model::InteractiveEntity *graphEntity);

public:
  void onGraphEntitySelected(model::InteractiveEntity *graphEntity);
  void onGraphEntityTargeted(model::InteractiveEntity *graphEntity);

private:
  model::ModelManager &modelManager;
  const model::EntitiesManager *entitiesManager;
  SelectionManager selectionManager;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
