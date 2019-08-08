#include "savefilesmanager.h"

#include <filesystem>

namespace how {
namespace model {
namespace {
using ios = ::std::ios;
namespace fs = ::std::filesystem;
const std::string SAVES_FOLDER_NAME = "./saves/";
} // namespace

void writeToFile(std::string fileName, json j) {
  fs::create_directory(SAVES_FOLDER_NAME);
  auto ofstream = std::ofstream(SAVES_FOLDER_NAME + fileName, ios::trunc);
  ofstream << std::setw(4) << j;
  ofstream.close();
}

json readFromFile(std::string fileName) {
  auto ifstream = std::ifstream(fileName);
  auto j = ::nlohmann::json();
  ifstream >> j;
  return j;
}

std::vector<std::string> getAllSaveFileNames() {
  auto saves = std::vector<std::string>();
  fs::create_directory(SAVES_FOLDER_NAME);
  for (const auto &entry : fs::directory_iterator(SAVES_FOLDER_NAME)) {
    saves.push_back(entry.path());
  }
  return saves;
}

} // namespace model
} // namespace how
