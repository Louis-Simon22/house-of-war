#ifndef CELLDATAOPERATIONS_H
#define CELLDATAOPERATIONS_H

#include <math.h>

#include "../graphtypes.h"
#include "../utils/easingfunctions.h"

namespace how {
namespace model {

template <typename CharacteristicReferenceAccessor>
void normalizeCellCharacteristic01(
    CharacteristicReferenceAccessor characteristicReferenceAccessor,
    types::graph_t &graph) {
  const auto &vertexSet = graph.vertex_set();
  const auto &minMaxPair = std::minmax_element(
      vertexSet.begin(), vertexSet.end(),
      [characteristicReferenceAccessor,
       &graph](types::graph_vertex_desc_t desc1,
               types::graph_vertex_desc_t desc2) -> bool {
        return characteristicReferenceAccessor(desc1, graph) <
               characteristicReferenceAccessor(desc2, graph);
      });
  const auto minVertexDesc = *std::get<0>(minMaxPair);
  const auto maxVertexDesc = *std::get<1>(minMaxPair);
  // Make sure these characteristics are a copy because they will get changed
  const auto minCharacteristicValue =
      characteristicReferenceAccessor(minVertexDesc, graph);
  const auto maxCharacteristicValue =
      characteristicReferenceAccessor(maxVertexDesc, graph);
  for (std::size_t i = 0; i < vertexSet.size(); i++) {
    auto &characteristicReference =
        characteristicReferenceAccessor(vertexSet[i], graph);
    characteristicReference =
        normalize01(characteristicReference, minCharacteristicValue,
                  maxCharacteristicValue);
  }
}

template <typename CharacteristicReferenceAccessor>
void normalizeCellCharacteristic11(
        CharacteristicReferenceAccessor characteristicReferenceAccessor,
        types::graph_t &graph) {
    const auto &vertexSet = graph.vertex_set();
    const auto &minMaxPair = std::minmax_element(
                vertexSet.begin(), vertexSet.end(),
                [characteristicReferenceAccessor,
                &graph](types::graph_vertex_desc_t desc1,
                types::graph_vertex_desc_t desc2) -> bool {
        return characteristicReferenceAccessor(desc1, graph) <
                characteristicReferenceAccessor(desc2, graph);
    });
    const auto minVertexDesc = *std::get<0>(minMaxPair);
    const auto maxVertexDesc = *std::get<1>(minMaxPair);
    // Make sure these characteristics are a copy because they will get changed
    const auto minCharacteristicValue =
            characteristicReferenceAccessor(minVertexDesc, graph);
    const auto maxCharacteristicValue =
            characteristicReferenceAccessor(maxVertexDesc, graph);
    for (std::size_t i = 0; i < vertexSet.size(); i++) {
        auto &characteristicReference =
                characteristicReferenceAccessor(vertexSet[i], graph);
        characteristicReference =
                normalize11(characteristicReference, minCharacteristicValue,
                          maxCharacteristicValue);
    }
}

// Sets the characteristic to the reverse of the fractional value for numbers
// with an uneven integral part. Leaves numbers with an even integral part
// unchanged
template <typename CharacteristicReferenceAccessor>
void reverseOverflowedCellCharacteristic(
    CharacteristicReferenceAccessor characteristicReferenceAccessor,
    types::graph_t &graph) {
  const auto &vertexSet = graph.vertex_set();
  for (std::size_t i = 0; i < vertexSet.size(); i++) {
    auto &characteristicReference =
        characteristicReferenceAccessor(vertexSet[i], graph);
    float integralPart;
    float fractionalPart = modff(characteristicReference, &integralPart);
    characteristicReference = static_cast<int>(integralPart) % 2 == 0
                                  ? fractionalPart
                                  : 1 - fractionalPart;
  }
}

template <typename CharacteristicReferenceAccessor>
void reverseCellCharacteristic(
    CharacteristicReferenceAccessor characteristicReferenceAccessor,
    types::graph_t &graph) {
  const auto &vertexSet = graph.vertex_set();
  for (std::size_t i = 0; i < vertexSet.size(); i++) {
    auto &characteristicReference =
        characteristicReferenceAccessor(vertexSet[i], graph);
    characteristicReference = 1 - characteristicReference;
  }
}

template <typename CharacteristicAssignmentFunction>
void distanceBasedCharacteristicSpread(
    types::graph_vertex_desc_t sourceVertexDesc,
    CharacteristicAssignmentFunction characteristicAssignmentFunction,
    types::graph_t &graph) {
  std::vector<types::coordinate_t> distances;
  std::tie(std::ignore, distances) = computeDijkstra(
      sourceVertexDesc,
      [](DelaunayEdge) -> types::coordinate_fpt_t { return 1; }, graph);
  const auto &greatestDistance =
      *std::max_element(distances.begin(), distances.end());
  for (std::size_t vertexDesc = 0; vertexDesc < distances.size();
       vertexDesc++) {
    const auto &distance = distances[vertexDesc];
    const auto value = normalize01(distance, 0, greatestDistance);
    characteristicAssignmentFunction(value, vertexDesc, graph);
  }
}

} // namespace model
} // namespace how

#endif // CELLDATAOPERATIONS_H
