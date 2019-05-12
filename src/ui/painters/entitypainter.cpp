#include "entitypainter.h"

namespace how {
namespace ui {

EntityPainter::EntityPainter(const model::GraphEntity &graphEntity,
                             QQuickItem *parent)
    : QQuickItem(parent), graphEntity(graphEntity) {
  this->setAntialiasing(true);
  this->setFlag(QQuickItem::ItemHasContents, true);
}

void EntityPainter::updateDimensions() {
  this->setX(static_cast<double>(this->graphEntity.getPosX()));
  this->setY(static_cast<double>(this->graphEntity.getPosY()));
  this->setZ(static_cast<double>(this->graphEntity.getLayer()));
  this->setWidth(static_cast<double>(this->graphEntity.getWidth()));
  this->setHeight(static_cast<double>(this->graphEntity.getHeight()));
  // TODO necessary?
  this->update();
}

EntityPainter::~EntityPainter() {}

} // namespace ui
} // namespace how
