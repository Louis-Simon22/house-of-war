#include "persistencemanager.h"

namespace how {
namespace model {
namespace {
using ios = ::std::ios;
}

std::ofstream serializeToFile(std::string fileName) {
  return std::ofstream(fileName, ios::out | ios::trunc);
}

} // namespace model
} // namespace how
