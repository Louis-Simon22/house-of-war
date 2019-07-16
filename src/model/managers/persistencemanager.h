#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <fstream>
#include <string>
#include <vector>

namespace how {
namespace model {

std::ofstream serializeToFile(std::string fileName);

} // namespace model
} // namespace how

#endif // PERSISTENCEMANAGER_H
