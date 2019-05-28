#include "armyitem.h"

namespace how {
namespace ui {

ArmyItem::ArmyItem(QQuickItem *parent, std::shared_ptr<model::Army> armyPtr)
    : GraphEntityItem(parent, armyPtr), armyPtr(armyPtr) {
    // TODO instantiate appropriate painters parented to this
    // TODO give a "reference" object to painters so they can map points to it
}

void ArmyItem::updateDimensions() {
  const auto scoutingRadius = this->armyPtr->getScoutingZone().getRadius();
  this->setX(static_cast<double>(this->armyPtr->getPosX() - scoutingRadius));
  this->setY(static_cast<double>(this->armyPtr->getPosY() - scoutingRadius));
  this->setZ(static_cast<double>(this->armyPtr->getLayer()));
  this->setWidth(static_cast<double>(scoutingRadius * 2));
  this->setHeight(static_cast<double>(scoutingRadius * 2));
}

} // namespace ui
} // namespace how
