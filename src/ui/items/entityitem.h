#ifndef ENTITYITEM_H
#define ENTITYITEM_H

#include <QQuickItem>

#include "../../model/entities/entity.h"

namespace how {
namespace ui {
class EntityItem : public QQuickItem {
  Q_OBJECT

public:
  EntityItem(model::Entity *entity, QQuickItem *parent);
  virtual ~EntityItem() = 0;

signals:
  void updateOnGuiThread();

private slots:
  virtual void onGraphEntityUpdated() = 0;

private:
  const model::Entity *entity;
  boost::signals2::connection entityChangedConnection;
};
} // namespace ui
} // namespace how

#endif // ENTITYITEM_H
