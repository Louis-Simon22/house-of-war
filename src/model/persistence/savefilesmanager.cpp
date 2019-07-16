#include "savefilesmanager.h"

#include <filesystem>

namespace how {
namespace model {
namespace {
using ios = ::std::ios;
namespace fs = ::std::filesystem;
const std::string SAVES_FOLDER_NAME = "./saves/";
} // namespace

void serializeToFile(std::string fileName, json j) {
  auto ofstream = std::ofstream(SAVES_FOLDER_NAME + fileName, ios::trunc);
  ofstream << std::setw(4) << j;
  ofstream.close();
}

json deserializeFile(std::string fileName) {
  auto ifstream = std::ifstream(fileName);
  auto j = ::nlohmann::json();
  ifstream >> j;
  return j;
}

std::vector<std::string> getAllSaveFileNames() {
  auto saves = std::vector<std::string>();
  for (const auto &entry : fs::directory_iterator(SAVES_FOLDER_NAME)) {
    saves.push_back(entry.path());
  }
  return saves;
}

} // namespace model
} // namespace how
