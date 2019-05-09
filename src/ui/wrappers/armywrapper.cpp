#include "armywrapper.h"

#include <QQmlEngine>

#include "../painters/armypainter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

ArmyWrapper::ArmyWrapper(model::Army &army)
    : SelectableEntityWrapper(), army(army) {}

ArmyWrapper::~ArmyWrapper() {}

EntityPainter *ArmyWrapper::createEntityPainter() const {
  return new ArmyPainter(this->army);
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

bool ArmyWrapper::isTargetable() const { return false; }

} // namespace ui
} // namespace how
