#include "entityitem.h"

namespace how {
namespace ui {

EntityItem::EntityItem(model::Entity *entity, QQuickItem *parent)
    : QQuickItem(parent), entity(entity), entityChangeConnection() {
  this->entityChangeConnection = entity->changeSignal.connect(
      std::bind(&EntityItem::updateOnGuiThread, this));
  connect(this, &EntityItem::updateOnGuiThread, this,
          &EntityItem::onGraphEntityUpdated, Qt::QueuedConnection);
}

EntityItem::~EntityItem() {}

} // namespace ui
} // namespace how
