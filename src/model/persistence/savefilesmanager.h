#ifndef SAVEFILESMANAGER_H
#define SAVEFILESMANAGER_H

#include <fstream>
#include <string>
#include <vector>

#include "../../../lib/json/single_include/nlohmann/json.hpp"

namespace how {
namespace model {
namespace {
using json = ::nlohmann::json;
}

void writeToFile(std::string fileName, json j);

json readFromFile(std::string fileName);

std::vector<std::string> getAllSaveFileNames();

} // namespace model
} // namespace how

#endif // SAVEFILESMANAGER_H
