#include "characterdataqmlwrapper.h"

namespace how {
namespace ui {
CharacterDataQMLWrapper::CharacterDataQMLWrapper() : QObject(nullptr) {}

CharacterDataQMLWrapper::CharacterDataQMLWrapper(
    model::CharacterData *characterDataPtr)
    : characterDataPtr(characterDataPtr) {}

CharactersModel *CharacterDataQMLWrapper::getCharactersModel() const {
  return new CharactersModel(this->characterDataPtr);
}
} // namespace ui
} // namespace how
