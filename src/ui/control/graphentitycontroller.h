#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <memory>

#include <QObject>
#include <QQuickItem>

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
  void progressAll(float deltaTime);
  void mousePressedOnGraphEntityPainter(
      QMouseEvent *event, std::shared_ptr<model::GraphEntity> graphEntityPtr);

private:
  QRect getWorldBounds() const;
  void
  onGraphEntitySelected(std::shared_ptr<model::GraphEntity> graphEntityPtr);
  void
  onGraphEntityTargeted(std::shared_ptr<model::GraphEntity> graphEntityPtr);

private:
  SelectionManager selectionManager;
  model::GraphEntityManager *graphEntityManagerPtr;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
