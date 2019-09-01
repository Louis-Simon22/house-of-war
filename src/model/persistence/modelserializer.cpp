#include "modelserializer.h"

#include <iostream>

#include "keys.h"

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
  return {{KEY_ENTITIES, serializeEntities(modelManager.getEntitiesManager())},
          {KEY_WORLD_GENERATION_CONFIG,
           serializeWorldGenerationConfig(
               modelManager.getWorldGenerationConfig())}};
  // TODO other model data
}

json serializeEntities(const EntitiesManager &entitiesManager) {
  auto serializedTiles = json::array();
  for (const auto &tilePtr : entitiesManager.getTilePtrs()) {
    serializedTiles.push_back(serializeTile(*tilePtr));
  }
  // TODO armies
  return {{KEY_TILES, serializedTiles}};
}

json serializeTile(const Tile &tile) {
  auto serializedEntity = serializeEntity(tile);

  auto serializedOutlinePoints = json::array();
  for (const auto &outlinePoint : tile.getOutlinePoints()) {
    serializedOutlinePoints.push_back(serializePoint(outlinePoint));
  }
  serializedEntity[KEY_TILE_OUTLINE_POINTS] = serializedOutlinePoints;
  serializedEntity[KEY_TILE_OUTLINE_TERRAIN_TYPE] =
      static_cast<int>(tile.getTerrainType());
  serializedEntity[KEY_TILE_OUTLINE_RESOURCES] = tile.getResources();

  return serializedEntity;
}

json serializeEntity(const Entity &entity) {
  return {{KEY_ENTITY_POSITION, serializePoint(entity.getPosition())}};
  // TODO serialize position changes
}

json serializePoint(const types::point_t &point) {
  return {{KEY_POINT_X, bg::get<0>(point)}, {KEY_POINT_Y, bg::get<1>(point)}};
}

json serializeBox(const types::box_t &box) {
  return {{KEY_BOX_MIN_CORNER, serializePoint(box.min_corner())},
          {KEY_BOX_MAX_CORNER, serializePoint(box.max_corner())}};
}

json serializeWorldGenerationConfig(const WorldGenerationConfig &config) {
  return {{KEY_WORLD_GENERATION_CONFIG_BOUNDING_BOX,
           serializeBox(config.boundingBox)},
          {KEY_WORLD_GENERATION_CONFIG_MINIMUM_VORONOI_CELL_DISTANCE,
           config.minimumVoronoiCellDistance},
          {KEY_WORLD_GENERATION_CONFIG_RANDOM_SEED, config.randomSeed}};
}

} // namespace model
} // namespace how
