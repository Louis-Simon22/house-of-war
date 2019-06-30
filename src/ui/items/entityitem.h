#ifndef ENTITYITEM_H
#define ENTITYITEM_H

#include <memory>

#include <QQuickItem>

#include "../../model/entities/entity.h"

namespace how {
namespace ui {
class EntityItem : public QQuickItem {
  Q_OBJECT

public:
  EntityItem(model::Entity *entity, QQuickItem *parent);
  virtual ~EntityItem() override = 0;

signals:
  void updateOnGuiThread();

private slots:
  virtual void onGraphEntityUpdated() = 0;

private:
  const model::Entity *entity;
};
} // namespace ui
} // namespace how

#endif // ENTITYITEM_H
