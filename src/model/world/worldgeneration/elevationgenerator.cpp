#include "elevationgenerator.h"

#include <iostream>
#include <noise/noise.h>

#include "../../easingfunctions.h"
#include "../graphoperations.h"
#include "./celldataoperations.h"
#include "./poissondisksamplingadapter.h"

namespace how {
namespace model {
namespace {
namespace nm = ::noise::module;
}

std::vector<std::vector<types::coordinate_t>>
generateHeightMap(std::uint32_t randomSeed) {
  constexpr std::size_t width = 255;
  constexpr std::size_t height = 255;
  auto heightMap = std::vector<std::vector<types::coordinate_t>>();

  auto baseTerrainModule = nm::Perlin();
  baseTerrainModule.SetOctaveCount(3);
  baseTerrainModule.SetFrequency(0.1);
  baseTerrainModule.SetSeed(static_cast<int>(randomSeed));
  auto flatTerrainModule = nm::ScaleBias();
  flatTerrainModule.SetSourceModule(0, baseTerrainModule);
  flatTerrainModule.SetBias(-0.75);
  flatTerrainModule.SetScale(0.125);
  auto baseMountainsModule = nm::Perlin();
  baseMountainsModule.SetOctaveCount(2);
  baseMountainsModule.SetFrequency(0.1);
  baseMountainsModule.SetPersistence(0.1);
  baseMountainsModule.SetSeed(static_cast<int>(randomSeed));
  auto mountainsTerraceModule = nm::Terrace();
  mountainsTerraceModule.SetSourceModule(0, baseMountainsModule);
  mountainsTerraceModule.AddControlPoint(0.25);
  mountainsTerraceModule.AddControlPoint(0.5);
  mountainsTerraceModule.AddControlPoint(0.75);
  auto controlModule = nm::Perlin();
  controlModule.SetOctaveCount(2);
  controlModule.SetFrequency(0.007);
  controlModule.SetPersistence(0.01);
  controlModule.SetSeed(static_cast<int>(randomSeed));
  auto selectModule = ::noise::module::Select();
  selectModule.SetSourceModule(0, flatTerrainModule);
  selectModule.SetSourceModule(1, mountainsTerraceModule);
  selectModule.SetControlModule(controlModule);
  selectModule.SetBounds(0, 1000.0);

  for (std::size_t i = 0; i < height; i++) {
    heightMap.push_back(std::vector<types::coordinate_t>());
    for (std::size_t j = 0; j < width; j++) {
      heightMap[i].push_back(static_cast<float>(controlModule.GetValue(
          static_cast<double>(i), static_cast<double>(j), 0)));
    }
  }

  return heightMap;
}

} // namespace model
} // namespace how
