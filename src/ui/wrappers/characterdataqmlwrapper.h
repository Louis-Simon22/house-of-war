#ifndef CHARACTERDATAQMLWRAPPER_H
#define CHARACTERDATAQMLWRAPPER_H

#include <QObject>
#include <memory>

#include "../../model/characters/character.h"
#include "../../model/characters/characterdata.h"
#include "../../model/characters/charactergeneration/charactergenerator.h"
#include "../../model/entities/movement/movementmanager.h"
#include "../models/charactersmodel.h"

namespace how {
namespace ui {
class CharacterDataQMLWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(CharactersModel *charactersModel READ getCharactersModel CONSTANT)

public:
  CharacterDataQMLWrapper();
  CharacterDataQMLWrapper(model::CharacterData *characterDataPtr);

private:
  CharactersModel *getCharactersModel() const;

private:
  model::CharacterData *characterDataPtr;
  std::unique_ptr<CharactersModel> charactersModelPtr;
};
} // namespace ui
} // namespace how

#endif // CHARACTERDATAQMLBINDINGS_H
