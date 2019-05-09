#include "maincontroller.h"

#include "../wrappers/armywrapper.h"
#include "../wrappers/characterwrapper.h"
#include "../wrappers/voronoicellwrapper.h"

namespace how {
namespace ui {

MainController::MainController()
    : modelManager(), modelThreadManager(), entityWrappers() {}

void MainController::instantiateEntityWrappers() {
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
    model::VoronoiCell &voronoiCell =
        worldManagerPtr->getVoronoiCellByDesc(*vertexIt);
    this->entityWrappers.push_back(
        std::unique_ptr<EntityWrapper>(new VoronoiCellWrapper(voronoiCell)));
  }
}

GraphEntityController *MainController::getGraphEntityController() {
  return new GraphEntityController(modelManager.getEntityChangeManagerPtr(),
                                   &this->entityWrappers);
}

EntitiesModel *MainController::getEntitiesModel() {
  return new EntitiesModel(&this->entityWrappers);
}

ModelManagerWrapper *MainController::getModelManagerWrapper() {
  return new ModelManagerWrapper(&this->modelManager);
}

} // namespace ui
} // namespace how
