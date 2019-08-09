#include "modeldeserializer.h"

#include <memory>

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
  auto tilePtrs = deserializeEntities(j["entities"]);
  auto worldGenerationConfig =
      deserializeWorldGenerationConfig(j["worldGenerationConfig"]);
  return std::make_tuple<>(worldGenerationConfig, tilePtrs);
}

std::vector<std::shared_ptr<Tile>> deserializeEntities(json j) {
  auto tilePtrs = std::vector<std::shared_ptr<Tile>>();
  auto tilesJson = j["tiles"];
  for (auto &tileJson : tilesJson) {
    tilePtrs.push_back(deserializeTile(tileJson));
  }
  return tilePtrs;
}

std::shared_ptr<Tile> deserializeTile(json j) {
  auto position = deserializePoint(j["position"]);

  auto outlinePointsJson = j["outlinePoints"];
  auto outlinePoints = std::vector<types::point_t>();
  for (auto &outlinePointJson : outlinePointsJson) {
    outlinePoints.push_back(deserializePoint(outlinePointJson));
  }

  auto tilePtr = std::make_shared<Tile>(position, outlinePoints);

  tilePtr->setTerrainType(static_cast<TerrainType>(j["terrainType"]));
  tilePtr->setResources(j["resources"]);
  return tilePtr;
}

types::point_t deserializePoint(json j) {
  return types::point_t(j["x"].get<types::coordinate_t>(),
                        j["y"].get<types::coordinate_t>());
}

types::box_t deserializeBox(json j) {
  return types::box_t(deserializePoint(j["minCorner"]),
                      deserializePoint(j["maxCorner"]));
}

WorldGenerationConfig deserializeWorldGenerationConfig(json j) {
  return WorldGenerationConfig(
      deserializeBox(j["boundingBox"]),
      j["minimumVoronoiCellDistance"].get<types::coordinate_t>(),
      j["randomSeed"].get<std::uint32_t>());
}

} // namespace model
} // namespace how
