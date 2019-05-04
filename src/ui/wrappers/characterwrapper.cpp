#include "characterwrapper.h"

#include "../painters/characterpainter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

CharacterWrapper::CharacterWrapper(model::Character &character)
    : character(character) {}

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

bool CharacterWrapper::isTargetable() const { return false; }

bool CharacterWrapper::isSelectable() const { return true; }

} // namespace ui
} // namespace how
