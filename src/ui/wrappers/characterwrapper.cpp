#include "characterwrapper.h"

#include "../painters/characterpainter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

CharacterWrapper::CharacterWrapper(model::Character &character)
    : SelectableEntityWrapper(), character(character) {}

EntityPainter *CharacterWrapper::createEntityPainter() const {
  return new CharacterPainter(this->character);
}

types::coordinate_t CharacterWrapper::getPosX() const {
  return bg::get<0>(this->character.getPosition());
}

types::coordinate_t CharacterWrapper::getPosY() const {
  return bg::get<1>(this->character.getPosition());
}

types::coordinate_t CharacterWrapper::getWidth() const { return 10; }

types::coordinate_t CharacterWrapper::getHeight() const { return 10; }

int CharacterWrapper::getLayer() const { return 2; }

bool CharacterWrapper::isTargetable() const { return false; }

} // namespace ui
} // namespace how
