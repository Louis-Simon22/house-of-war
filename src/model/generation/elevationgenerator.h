#ifndef HEIGHTGENERATOR_H
#define HEIGHTGENERATOR_H

#include <noise/noise.h>

#include "../graphtypes.h"

namespace how {
namespace model {
namespace {
namespace nm = ::noise::module;
}

nm::Module *generateHeightMap(std::uint32_t randomSeed);

} // namespace model
} // namespace how

#endif // HEIGHTGENERATOR_H
