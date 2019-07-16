#ifndef MODELDESERIALIZER_H
#define MODELDESERIALIZER_H

#include "../../../lib/json/single_include/nlohmann/json.hpp"

#include "../managers/modelmanager.h"

namespace how {
namespace model {
namespace {
using json = ::nlohmann::json;
}

void deserializeModel(ModelManager &modelManager, json j);

} // namespace model
} // namespace how

#endif // MODELDESERIALIZER_H
