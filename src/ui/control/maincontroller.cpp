#include "maincontroller.h"

#include "../wrappers/armywrapper.h"
#include "../wrappers/characterwrapper.h"
#include "../wrappers/voronoicellwrapper.h"

namespace how {
namespace ui {

MainController::MainController()
    : modelManager(), modelThreadManager(), entityWrappers(),
      entityControllerPtr(), armyControllerPtr(), characterControllerPtr(),
      entitiesModelPtr(), worldManagerWrapperPtr() {}

void MainController::newModel(int width, int height,
                              float minimumVoronoiCellDistance,
                              int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->instantiateUiElements();
  this->newModelGenerated();
}

void MainController::instantiateUiElements() {
  this->worldManagerWrapperPtr.reset(
      new WorldManagerWrapper(this->modelManager.getWorldManagerPtr()));
  this->armyControllerPtr.reset(new ArmyController());
  this->characterControllerPtr.reset(new CharacterController());
  auto &armies = modelManager.getGraphEntityManagerPtr()->getArmies();

  for (auto &army : armies) {
    this->entityWrappers.push_back(
        std::unique_ptr<EntityWrapper>(new ArmyWrapper(army)));
  }
  auto &characters =
      this->modelManager.getGraphEntityManagerPtr()->getCharacters();
  for (auto &character : characters) {
    this->entityWrappers.push_back(
        std::unique_ptr<EntityWrapper>(new CharacterWrapper(character)));
  }
  auto *worldManagerPtr = this->modelManager.getWorldManagerPtr();
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  ::boost::tie(vertexItBegin, vertexItEnd) =
      ::boost::vertices(worldManagerPtr->getGraph());
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    const auto vertexDesc = *vertexIt;
    model::VoronoiCell &voronoiCell =
        worldManagerPtr->getVoronoiCellByDesc(vertexDesc);
    this->entityWrappers.push_back(std::unique_ptr<EntityWrapper>(
        new VoronoiCellWrapper(vertexDesc, voronoiCell)));
  }

  this->entityControllerPtr.reset(new EntityController(
      this->modelManager.getEntityChangeManagerPtr(), &this->entityWrappers));
  this->entitiesModelPtr.reset(new EntitiesModel(&this->entityWrappers));
}

EntityController *MainController::getEntityController() {
  return this->entityControllerPtr.get();
}

EntitiesModel *MainController::getEntitiesModel() {
  return this->entitiesModelPtr.get();
}

WorldManagerWrapper *MainController::getWorldManagerWrapper() {
  return this->worldManagerWrapperPtr.get();
}

} // namespace ui
} // namespace how
