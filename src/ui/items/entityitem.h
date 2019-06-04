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
  EntityItem(std::shared_ptr<model::Entity> entityPtr, QQuickItem *parent);
  virtual ~EntityItem() override = 0;

signals:
  void updateOnGuiThread();

private slots:
  virtual void onGraphEntityUpdated() = 0;

private:
  std::shared_ptr<const model::Entity> entityPtr;
};
} // namespace ui
} // namespace how

#endif // ENTITYITEM_H
