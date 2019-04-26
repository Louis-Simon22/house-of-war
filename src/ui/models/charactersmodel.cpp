#include "charactersmodel.h"

namespace how {
namespace ui {

CharactersModel::CharactersModel()
    : EntityModel(), graphEntityManagerPtr(nullptr) {}

CharactersModel::CharactersModel(
    const model::GraphEntityManager *graphEntityManagerPtr)
    : EntityModel(), graphEntityManagerPtr(graphEntityManagerPtr) {
  const auto &characters = graphEntityManagerPtr->getCharacters();
  for (std::size_t i = 0; i < characters.size(); i++) {
    this->uuidToIndexMap[characters[i].getUuid()] =
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
  return static_cast<int>(this->graphEntityManagerPtr->getCharacters().size());
}

QVariant CharactersModel::data(const QModelIndex &index, int role) const {
  const auto &character =
      this->graphEntityManagerPtr
          ->getCharacters()[static_cast<std::size_t>(index.row())];
  switch (role) {
  case PosX:
    return bg::get<0>(character.getPosition());
  case PosY:
    return bg::get<1>(character.getPosition());
  default:
    return 0;
  }
}

} // namespace ui
} // namespace how
