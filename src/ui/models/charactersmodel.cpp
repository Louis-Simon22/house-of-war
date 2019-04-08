#include "charactersmodel.h"

namespace how {
namespace ui {

CharactersModel::CharactersModel() : EntityModel(), characterDataPtr(nullptr) {}

CharactersModel::CharactersModel(const model::CharacterData *characterDataPtr)
    : EntityModel(), characterDataPtr(characterDataPtr) {
  const auto *characters = characterDataPtr->getCharacters();
  for (std::size_t i = 0; i < characters->size(); i++) {
    this->uuidToIndexMap[characters->operator[](i).uuid] =
        this->index(static_cast<int>(i));
  }
}

QHash<int, QByteArray> CharactersModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[PosX] = "posX";
  roles[PosY] = "posY";
  return roles;
}

Qt::ItemFlags CharactersModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable;
}

QVariant CharactersModel::headerData(int, Qt::Orientation, int) const {
  return QVariant();
}

int CharactersModel::rowCount(const QModelIndex &) const {
  return static_cast<int>(this->characterDataPtr->getCharacters()->size());
}

QVariant CharactersModel::data(const QModelIndex &index, int role) const {
  const auto &character = this->characterDataPtr->getCharacters()->operator[](
      static_cast<std::size_t>(index.row()));
  switch (role) {
  case PosX:
    return bg::get<0>(character.position);
  case PosY:
    return bg::get<1>(character.position);
  default:
    return 0;
  }
}

} // namespace ui
} // namespace how
