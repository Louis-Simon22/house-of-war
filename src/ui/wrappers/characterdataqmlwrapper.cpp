#include "characterdataqmlwrapper.h"

namespace how {
namespace ui {
CharacterDataQMLWrapper::CharacterDataQMLWrapper() : QObject(nullptr) {}

CharacterDataQMLWrapper::CharacterDataQMLWrapper(
    model::CharacterData *characterDataPtr)
    : characterDataPtr(characterDataPtr),
      charactersModelPtr(std::make_unique<CharactersModel>(characterDataPtr)) {}

CharactersModel *CharacterDataQMLWrapper::getCharactersModel() const {
  return charactersModelPtr.get();
}
} // namespace ui
} // namespace how
