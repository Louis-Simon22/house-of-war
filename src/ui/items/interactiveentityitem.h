#ifndef INTERACTIVEENTITYITEM_H
#define INTERACTIVEENTITYITEM_H

#include "../../model/entities/interactiveentity.h"
#include "./entityitem.h"

namespace how {
namespace ui {
class InteractiveEntityItem : public EntityItem {
  Q_OBJECT

public:
  InteractiveEntityItem(
      std::shared_ptr<model::InteractiveEntity> interactiveEntityPtr,
      QQuickItem *parent);
  virtual ~InteractiveEntityItem() override = 0;

signals:
  void updateOnGuiThread();
  void
  mousePressedOnGraphEntityPainter(QMouseEvent *event,
                                   model::InteractiveEntity *interactiveEntity);

public:
  void mousePressEvent(QMouseEvent *event) override;

private:
  void updateAcceptedMouseButtons();

private:
  std::shared_ptr<model::InteractiveEntity> interactiveEntityPtr;
};
} // namespace ui
} // namespace how

#endif // INTERACTIVEENTITYITEM_H
