#include "entitypainter.h"

#include <boost/signals2.hpp>

namespace how {
namespace ui {
namespace {
namespace bs = ::boost::signals2;
}

EntityPainter::EntityPainter(model::GraphEntity &graphEntity,
                             QQuickItem *parent)
    : QQuickItem(parent), graphEntity(graphEntity) {
  this->setAntialiasing(true);
  this->setFlag(QQuickItem::ItemHasContents, true);
  this->updateDimensions();
}

void EntityPainter::updateDimensions() {
  this->setX(static_cast<double>(this->graphEntity.getPosX()));
  this->setY(static_cast<double>(this->graphEntity.getPosY()));
  this->setZ(static_cast<double>(this->graphEntity.getLayer()));
  this->setWidth(static_cast<double>(this->graphEntity.getWidth()));
  this->setHeight(static_cast<double>(this->graphEntity.getHeight()));
}

model::GraphEntity &EntityPainter::getGraphEntity() {
  return this->graphEntity;
}

EntityPainter::~EntityPainter() {}

} // namespace ui
} // namespace how
