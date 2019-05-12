#ifndef VORONOICELLWRAPPER_H
#define VORONOICELLWRAPPER_H

#include "../../model/entities/voronoicell.h"
#include "../../model/graphtypes.h"
#include "./entitywrapper.h"

namespace how {
namespace ui {
class VoronoiCellWrapper : public EntityWrapper {
public:
  VoronoiCellWrapper(types::graph_vertex_desc_t vertexDesc,
                     model::VoronoiCell &voronoiCell);
  ~VoronoiCellWrapper() override;

public:
  EntityPainter *createEntityPainter() const override;
  types::coordinate_t getPosX() const override;
  types::coordinate_t getPosY() const override;
  types::coordinate_t getWidth() const override;
  types::coordinate_t getHeight() const override;
  int getLayer() const override;
  types::graph_vertex_desc_t getVertexDesc() const override;
  bool isTargetable() const override;
  bool isSelectable() const override;

public:
  void onEntityWrapperTargeted(EntityWrapper *target) override;

public:
  model::VoronoiCell &getVoronoiCell();
  const model::VoronoiCell &getVoronoiCell() const;

private:
  types::graph_vertex_desc_t vertexDesc;
  model::VoronoiCell &voronoiCell;  
};
} // namespace ui
} // namespace how

#endif // VORONOICELLWRAPPER_H
