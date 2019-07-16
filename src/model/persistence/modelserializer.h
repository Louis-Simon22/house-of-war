#ifndef MODELSERIALIZER_H
#define MODELSERIALIZER_H

#include "../../../lib/json/single_include/nlohmann/json.hpp"

#include "../managers/modelmanager.h"

namespace how {
namespace model {
namespace {
using json = ::nlohmann::json;
}

json serializeModel(const ModelManager& modelManager);

}
}

#endif // MODELSERIALIZER_H
