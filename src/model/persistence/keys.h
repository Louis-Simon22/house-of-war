#ifndef KEYS_H
#define KEYS_H

#include <string>

namespace how {
namespace model {
static const std::string KEY_ENTITIES = "entities";
static const std::string KEY_WORLD_GENERATION_CONFIG = "worldGenerationConfig";
static const std::string KEY_WORLD_GENERATION_CONFIG_BOUNDING_BOX =
    "boundingBox";
static const std::string
    KEY_WORLD_GENERATION_CONFIG_MINIMUM_VORONOI_CELL_DISTANCE =
        "minimumVoronoiCellDistance";
static const std::string KEY_WORLD_GENERATION_CONFIG_RANDOM_SEED = "randomSeed";
static const std::string KEY_ENTITY_POSITION = "position";
static const std::string KEY_ENTITY_LAYER = "layer";
static const std::string KEY_TILES = "tiles";
static const std::string KEY_TILE_OUTLINE_POINTS = "outlinePoints";
static const std::string KEY_TILE_OUTLINE_TERRAIN_TYPE = "terrainType";
static const std::string KEY_TILE_OUTLINE_RESOURCES = "resources";
static const std::string KEY_POINT_X = "x";
static const std::string KEY_POINT_Y = "y";
static const std::string KEY_BOX = "minCorner";
static const std::string KEY_BOX_MIN_CORNER = "minCorner";
static const std::string KEY_BOX_MAX_CORNER = "maxCorner";
} // namespace model
} // namespace how
#endif // KEYS_H
