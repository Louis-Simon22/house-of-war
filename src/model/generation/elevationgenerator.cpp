#include "elevationgenerator.h"

#include "../operations/celldataoperations.h"
#include "../operations/graphoperations.h"
#include "../utils/easingfunctions.h"
#include "./poissondisksamplingadapter.h"

namespace how {
namespace model {

// TODO all these initializations in an adaptor object
// TODO the sea
nm::Module *generateHeightMap(std::uint32_t randomSeed) {
  // Base terrain
  auto *baseTerrainModule = new nm::Billow();
  baseTerrainModule->SetOctaveCount(12);
  baseTerrainModule->SetFrequency(24.0);
  baseTerrainModule->SetPersistence(0.5);
  baseTerrainModule->SetSeed(static_cast<int>(randomSeed++));
  auto *flatTerrainModule = new nm::ScaleBias();
  flatTerrainModule->SetSourceModule(0, *baseTerrainModule);
  flatTerrainModule->SetBias(0);
  flatTerrainModule->SetScale(0.05);

  // Moutains
  auto *baseMountainsModule = new nm::Perlin();
  baseMountainsModule->SetOctaveCount(12);
  baseMountainsModule->SetFrequency(4);
  baseMountainsModule->SetPersistence(0.5);
  baseMountainsModule->SetSeed(static_cast<int>(randomSeed++));
  auto *mountainsTerraceModule = new nm::Terrace();
  mountainsTerraceModule->SetSourceModule(0, *baseMountainsModule);
  mountainsTerraceModule->AddControlPoint(0.30);
  mountainsTerraceModule->AddControlPoint(0.75);
  auto *mountainousTerrain = new nm::Add();
  mountainousTerrain->SetSourceModule(0, *mountainsTerraceModule);
  mountainousTerrain->SetSourceModule(1, *flatTerrainModule);

  return mountainousTerrain;
}

} // namespace model
} // namespace how
