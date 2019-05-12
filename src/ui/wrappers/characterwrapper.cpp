#include "characterwrapper.h"

#include "../painters/characterpainter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

CharacterWrapper::CharacterWrapper(CharacterController &characterController,
                                   model::Character &character)
    : EntityWrapper(), characterController(characterController),
      character(character) {}

CharacterWrapper::~CharacterWrapper() {}

EntityPainter *CharacterWrapper::createEntityPainter() const {
  return new CharacterPainter(*this);
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

types::graph_vertex_desc_t CharacterWrapper::getVertexDesc() const {
  return this->character.getCurrentVertexDesc();
}

bool CharacterWrapper::isTargetable() const { return false; }

bool CharacterWrapper::isSelectable() const { return true; }

void CharacterWrapper::onEntityWrapperTargeted(EntityWrapper *target) {
  this->characterController.moveCharacterTo(*this, target);
}

model::Character &CharacterWrapper::getCharacter() { return this->character; }

const model::Character &CharacterWrapper::getCharacter() const {
  return this->character;
}

} // namespace ui
} // namespace how
