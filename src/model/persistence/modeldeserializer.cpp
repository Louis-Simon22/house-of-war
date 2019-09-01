#include "modeldeserializer.h"

#include <iostream>
#include <memory>

#include "keys.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

std::vector<std::shared_ptr<Tile>> deserializeEntities(json j);
std::shared_ptr<Tile> deserializeTile(json j);
types::point_t deserializePoint(json j);
types::box_t deserializeBox(json j);
WorldGenerationConfig deserializeWorldGenerationConfig(json j);

std::tuple<WorldGenerationConfig, std::vector<std::shared_ptr<Tile>>>
deserializeModel(json j) {
  auto tilePtrs = deserializeEntities(j[KEY_ENTITIES]);
  auto worldGenerationConfig =
      deserializeWorldGenerationConfig(j[KEY_WORLD_GENERATION_CONFIG]);
  return std::make_tuple<>(worldGenerationConfig, tilePtrs);
}

std::vector<std::shared_ptr<Tile>> deserializeEntities(json j) {
  auto tilePtrs = std::vector<std::shared_ptr<Tile>>();
  auto tilesJson = j[KEY_TILES];
  for (auto &tileJson : tilesJson) {
    tilePtrs.push_back(deserializeTile(tileJson));
  }
  return tilePtrs;
}

std::shared_ptr<Tile> deserializeTile(json j) {
  auto position = deserializePoint(j[KEY_ENTITY_POSITION]);

  auto outlinePointsJson = j[KEY_TILE_OUTLINE_POINTS];
  auto outlinePoints = std::vector<types::point_t>();
  for (auto &outlinePointJson : outlinePointsJson) {
    outlinePoints.push_back(deserializePoint(outlinePointJson));
  }

  auto tilePtr = std::make_shared<Tile>(position, outlinePoints);
  tilePtr->setTerrainType(
      static_cast<TerrainType>(j[KEY_TILE_OUTLINE_TERRAIN_TYPE]));
  tilePtr->setResources(j[KEY_TILE_OUTLINE_RESOURCES]);

  return tilePtr;
}

types::point_t deserializePoint(json j) {
  return types::point_t(j[KEY_POINT_X].get<types::coordinate_t>(),
                        j[KEY_POINT_Y].get<types::coordinate_t>());
}

types::box_t deserializeBox(json j) {
  return types::box_t(deserializePoint(j[KEY_BOX_MIN_CORNER]),
                      deserializePoint(j[KEY_BOX_MAX_CORNER]));
}

WorldGenerationConfig deserializeWorldGenerationConfig(json j) {
  return WorldGenerationConfig(
      deserializeBox(j[KEY_WORLD_GENERATION_CONFIG_BOUNDING_BOX]),
      j[KEY_WORLD_GENERATION_CONFIG_MINIMUM_VORONOI_CELL_DISTANCE]
          .get<types::coordinate_t>(),
      j[KEY_WORLD_GENERATION_CONFIG_RANDOM_SEED].get<std::uint32_t>());
}

} // namespace model
} // namespace how
