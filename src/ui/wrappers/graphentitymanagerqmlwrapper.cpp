#include "graphentitymanagerqmlwrapper.h"

namespace how {
namespace ui {
GraphEntityManagerQMLWrapper::GraphEntityManagerQMLWrapper()
    : QObject(nullptr), graphEntityManagerPtr(nullptr) {}

GraphEntityManagerQMLWrapper::GraphEntityManagerQMLWrapper(
    model::GraphEntityManager *graphEntityManagerPtr)
    : graphEntityManagerPtr(graphEntityManagerPtr),
      charactersModelPtr(
          std::make_unique<CharactersModel>(graphEntityManagerPtr)),
      armiesModelPtr(std::make_unique<ArmiesModel>(graphEntityManagerPtr)) {}

CharactersModel *GraphEntityManagerQMLWrapper::getCharactersModel() const {
  return this->charactersModelPtr.get();
}

ArmiesModel *GraphEntityManagerQMLWrapper::getArmiesModel() const {
  return this->armiesModelPtr.get();
}
} // namespace ui
} // namespace how
