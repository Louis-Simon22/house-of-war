#include "modelmanagerwrapper.h"

#include <memory>

#include <QQmlEngine>

#include "../../model/generation/worldgenerationconfig.h"
#include "../conversion/converter.h"
#include "./armywrapper.h"
#include "./characterwrapper.h"
#include "./entitywrapper.h"
#include "./voronoicellwrapper.h"

#include <iostream>

namespace how {
namespace ui {

ModelManagerWrapper::ModelManagerWrapper(QObject *parent)
    : QObject(parent), modelManager(model::ModelManager()),
      modelThreadManager(), entityWrappers() {}

void ModelManagerWrapper::newModel(int width, int height,
                                   float minimumVoronoiCellDistance,
                                   int randomSeed) {
  this->modelThreadManager.pauseIterations();
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->instantiateEntityWrappers();
  this->newModelGenerated();
}

void ModelManagerWrapper::instantiateEntityWrappers() {
  auto &armies = this->modelManager.getGraphEntityManagerPtr()->getArmies();
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

GraphEntityController *ModelManagerWrapper::getGraphEntityController() {
  return new GraphEntityController(modelManager.getEntityChangeManagerPtr(),
                                   &this->entityWrappers);
}

EntitiesModel *ModelManagerWrapper::getEntitiesModel() {
  return new EntitiesModel(&this->entityWrappers);
}

QRect ModelManagerWrapper::getWorldBounds() const {
  return convert(this->modelManager.getWorldManagerPtr()->getBounds());
}

} // namespace ui
} // namespace how
