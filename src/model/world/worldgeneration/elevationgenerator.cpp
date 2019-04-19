#include "elevationgenerator.h"

#include "../../easingfunctions.h"
#include "../graphoperations.h"
#include "./celldataoperations.h"
#include "./poissondisksamplingadapter.h"

#include <iostream>

namespace how {
namespace model {

// TODO all these initializations in an adaptor object
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
  flatTerrainModule->SetScale(0.20);

  // Moutains
  auto *baseMountainsModule = new nm::Perlin();
  baseMountainsModule->SetOctaveCount(12);
  baseMountainsModule->SetFrequency(4);
  baseMountainsModule->SetPersistence(0.5);
  baseMountainsModule->SetSeed(static_cast<int>(randomSeed++));
  auto *mountainsTerraceModule = new nm::Terrace();
  mountainsTerraceModule->SetSourceModule(0, *baseMountainsModule);
  mountainsTerraceModule->AddControlPoint(0.40);
  mountainsTerraceModule->AddControlPoint(0.75);
  auto *mountainousTerrain = new nm::Add();
  mountainousTerrain->SetSourceModule(0, *mountainsTerraceModule);
  mountainousTerrain->SetSourceModule(1, *flatTerrainModule);

  // Fusion
  auto *controlModule = new nm::Perlin();
  controlModule->SetOctaveCount(6);
  controlModule->SetFrequency(1);
  controlModule->SetPersistence(0.5);
  controlModule->SetSeed(static_cast<int>(randomSeed++));
  auto *selectModule = new nm::Select();
  selectModule->SetSourceModule(0, *flatTerrainModule);
  selectModule->SetSourceModule(1, *mountainousTerrain);
  selectModule->SetControlModule(*controlModule);
  selectModule->SetBounds(0, 1000.0);
  selectModule->SetEdgeFalloff(0.01);

  return selectModule;
}

} // namespace model
} // namespace how
