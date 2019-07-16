#include "entityitem.h"

namespace how {
namespace ui {

EntityItem::EntityItem(model::Entity *entity, QQuickItem *parent)
    : QQuickItem(parent), entity(entity), entityChangedConnection() {
  this->entityChangedConnection = entity->changedSignal.connect(
      ::boost::bind(&EntityItem::updateOnGuiThread, this));
  connect(this, &EntityItem::updateOnGuiThread, this,
          &EntityItem::onGraphEntityUpdated, Qt::QueuedConnection);
}

EntityItem::~EntityItem() { this->entityChangedConnection.disconnect(); }

} // namespace ui
} // namespace how
