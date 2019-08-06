#ifndef MODELDESERIALIZER_H
#define MODELDESERIALIZER_H

#include "../../../lib/json/single_include/nlohmann/json.hpp"

#include "../managers/modelmanager.h"

namespace how {
namespace model {
namespace {
using json = ::nlohmann::json;
}

std::tuple<WorldGenerationConfig, std::vector<std::shared_ptr<Tile>>>
deserializeModel(json j);

} // namespace model
} // namespace how

#endif // MODELDESERIALIZER_H
