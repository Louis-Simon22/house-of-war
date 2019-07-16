#include "modelserializer.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

json serializeEntities(const EntitiesManager &entitiesManager);
json serializeEntity(const Entity &entity);
json serializeTile(const Tile &tile);
json serializeWorldGenerationConfig(const WorldGenerationConfig &config);
json serializeBox(const types::box_t &box);
json serializePoint(const types::point_t &point);

json serializeModel(const ModelManager &modelManager) {
  return {
      {"entities", serializeEntities(modelManager.getEntitiesManager())},
      {"worldGenerationConfig",
       serializeWorldGenerationConfig(modelManager.getWorldGenerationConfig())}
  };
  // TODO other model data
}

json serializeEntities(const EntitiesManager &entitiesManager) {
  auto serializedTiles = json::array();
  for (const auto &tilePtr : entitiesManager.getTilePtrs()) {
    serializedTiles.push_back(serializeTile(*tilePtr));
  }
  // TODO armies
  return {{"tiles", serializedTiles}};
}

json serializeTile(const Tile &tile) {
  auto serializedEntity = serializeEntity(tile);

  auto serializedOutlinePoints = json::array();
  for (const auto &outlinePoint : tile.getOutlinePoints()) {
    serializedOutlinePoints.push_back(serializePoint(outlinePoint));
  }

  serializedEntity["outlinePoints"] = serializedOutlinePoints;
  return serializedEntity;
}

json serializeEntity(const Entity &entity) {
  return {{"layer", entity.getLayer()},
          {"position", serializePoint(entity.getPosition())}};
  // TODO serialize position changes
}

json serializePoint(const types::point_t &point) {
  return {{"x", bg::get<0>(point)}, {"y", bg::get<1>(point)}};
}

json serializeBox(const types::box_t &box) {
  return {{"minCorner", serializePoint(box.min_corner())},
          {"maxCorner", serializePoint(box.max_corner())}};
}

json serializeWorldGenerationConfig(const WorldGenerationConfig &config) {
  return {{"boundingBox", serializeBox(config.boundingBox)},
          {"minimumVoronoiCellDistance", config.minimumVoronoiCellDistance},
          {"randomSeed", config.randomSeed}};
}

} // namespace model
} // namespace how
