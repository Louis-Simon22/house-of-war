#include "armywrapper.h"

#include <QQmlEngine>

#include "../painters/armypainter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

ArmyWrapper::ArmyWrapper(ArmyController &armyController, model::Army &army)
    : EntityWrapper(), armyController(armyController), army(army) {}

ArmyWrapper::~ArmyWrapper() {}

EntityPainter *ArmyWrapper::createEntityPainter() const {
  return new ArmyPainter(*this);
}

types::coordinate_t ArmyWrapper::getPosX() const {
  return bg::get<0>(this->army.getPosition());
}

types::coordinate_t ArmyWrapper::getPosY() const {
  return bg::get<1>(this->army.getPosition());
}

types::coordinate_t ArmyWrapper::getWidth() const { return 10; }

types::coordinate_t ArmyWrapper::getHeight() const { return 10; }

int ArmyWrapper::getLayer() const { return 1; }

types::graph_vertex_desc_t ArmyWrapper::getVertexDesc() const {
  return this->army.getCurrentVertexDesc();
}

bool ArmyWrapper::isTargetable() const { return false; }

bool ArmyWrapper::isSelectable() const { return true; }

void ArmyWrapper::onEntityWrapperTargeted(EntityWrapper *target) {
  this->armyController.moveArmyTo(*this, target);
}

model::Army &ArmyWrapper::getArmy() { return this->army; }

const model::Army &ArmyWrapper::getArmy() const { return this->army; }

} // namespace ui
} // namespace how
