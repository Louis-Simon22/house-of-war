#include "entityitem.h"

namespace how {
namespace ui {

EntityItem::EntityItem(std::shared_ptr<model::Entity> entityPtr,
                       QQuickItem *parent)
    : QQuickItem(parent), entityPtr(entityPtr) {
  entityPtr->changedSignal.connect(
      ::boost::bind(&EntityItem::updateOnGuiThread, this));
  connect(this, &EntityItem::updateOnGuiThread, this,
          &EntityItem::onGraphEntityUpdated, Qt::QueuedConnection);
}

EntityItem::~EntityItem() {}

} // namespace ui
} // namespace how
