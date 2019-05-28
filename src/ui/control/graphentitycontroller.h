#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <QMouseEvent>
#include <QObject>

#include "../../model/managers/graphentitymanager.h"
#include "./selectionmanager.h"

namespace how {
namespace ui {
class GraphEntityController : public QObject {
  Q_OBJECT

  Q_PROPERTY(QRect worldBounds READ getWorldBounds CONSTANT FINAL)

public:
  GraphEntityController(model::GraphEntityManager *graphEntityManagerPtr);

public slots:
  void mousePressedOnGraphEntityPainter(QMouseEvent *event,
                                        model::GraphEntity *graphEntity);

private:
  QRect getWorldBounds() const;
  void onGraphEntitySelected(model::GraphEntity *graphEntity);
  void onGraphEntityTargeted(model::GraphEntity *graphEntity);

private:
  SelectionManager selectionManager;
  model::GraphEntityManager *graphEntityManagerPtr;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
