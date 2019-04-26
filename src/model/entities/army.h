#ifndef ARMY_H
#define ARMY_H


#include "../modeltypes.h"
#include "../graphtypes.h"
#include "./graphentity.h"

namespace how {
namespace model {
class Army : public GraphEntity {
public:
  Army(types::point_t initialPosition,
       types::graph_vertex_desc_t currentVertexIndex);
  ~Army() override;

public:
  void onIteration(float deltaTime);

private:
  types::coordinate_t influenceAreaWidth = 50;
};
} // namespace model
} // namespace how

#endif // ARMY_H
