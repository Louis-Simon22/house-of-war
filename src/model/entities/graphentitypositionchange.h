#ifndef GRAPHMOVEMENT_H
#define GRAPHMOVEMENT_H

#include "./graphentitychange.h"
#include "./voronoicell.h"

namespace how {
namespace model {
class GraphEntityPositionChange : public GraphEntityChange {
public:
  GraphEntityPositionChange(GraphEntity *entity,
                            std::vector<VoronoiCell *> destinations);
  ~GraphEntityPositionChange() override;

public:
  bool progress(float deltaTime) override;
  void destinationReached() override;

private:
  GraphEntity *graphEntity;
  std::vector<VoronoiCell *> destinations;
  std::size_t currentDestinationIndex;
};
} // namespace model
} // namespace how

#endif // GRAPHMOVEMENT_H
