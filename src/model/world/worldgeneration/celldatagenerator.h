#ifndef CELLDATAGENERATOR_H
#define CELLDATAGENERATOR_H

#include <iostream>

#include "../../delaunaygraphtypes.h"
#include "./characteristicspreader.h"

namespace how {
namespace model {

template <typename CharacteristicReferenceAccessor>
void distanceBasedCharacteristicGeneration(
    types::delaunay_graph_vertex_desc_t sourceVertex,
    CharacteristicReferenceAccessor characteristicReferenceAccessor,
    types::delaunay_graph_t &graph) {
  spreadCharacteristic<>(
      sourceVertex,
      [characteristicReferenceAccessor](
          types::characteristics_t value,
          types::delaunay_graph_vertex_desc_t vertexDesc,
          types::delaunay_graph_t &graph) -> void {
        auto &characteristicReference =
            characteristicReferenceAccessor(vertexDesc, graph);
        if (characteristicReferenceAccessor(vertexDesc, graph) == 0.0F) {
          characteristicReferenceAccessor(vertexDesc, graph) +=
              flip(smoothEnd<2>(value));
        }
      },
      graph);
}

template <typename CharacteristicReferenceAccessor>
void normalizeCellCharacteristic(
    CharacteristicReferenceAccessor characteristicReferenceAccessor,
    types::delaunay_graph_t &graph) {
  const auto &vertexSet = graph.vertex_set();
  const auto &previousMaxCharacteristicVertexDesc =
      *std::max_element(vertexSet.begin(), vertexSet.end(),
                        [characteristicReferenceAccessor, &graph](
                            types::delaunay_graph_vertex_desc_t desc1,
                            types::delaunay_graph_vertex_desc_t desc2) -> bool {
                          return characteristicReferenceAccessor(desc1, graph) <
                                 characteristicReferenceAccessor(desc2, graph);
                        });
  const auto &previousMaxCharacteristic = characteristicReferenceAccessor(
      previousMaxCharacteristicVertexDesc, graph);
  std::cout << previousMaxCharacteristic << std::endl;
  for (std::size_t i = 0; i < vertexSet.size(); i++) {
    auto &characteristicReference =
        characteristicReferenceAccessor(vertexSet[i], graph);
    characteristicReference =
        normalize(characteristicReference, 0, previousMaxCharacteristic);
  }
}

} // namespace model
} // namespace how

#endif // CELLDATAGENERATOR_H
