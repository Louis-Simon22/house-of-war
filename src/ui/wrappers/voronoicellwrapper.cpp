#include "voronoicellwrapper.h"

#include "../painters/voronoicellpainter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

VoronoiCellWrapper::VoronoiCellWrapper(types::graph_vertex_desc_t vertexDesc,
                                       model::VoronoiCell &voronoiCell)
    : EntityWrapper(), vertexDesc(vertexDesc), voronoiCell(voronoiCell) {}

VoronoiCellWrapper::~VoronoiCellWrapper() {}

EntityPainter *VoronoiCellWrapper::createEntityPainter() const {
  return new VoronoiCellPainter(*this);
}

types::coordinate_t VoronoiCellWrapper::getPosX() const {
  return bg::get<bg::min_corner, 0>(this->voronoiCell.getEnvelope());
}

types::coordinate_t VoronoiCellWrapper::getPosY() const {
  return bg::get<bg::min_corner, 1>(this->voronoiCell.getEnvelope());
}

types::coordinate_t VoronoiCellWrapper::getWidth() const {
  return bg::get<bg::max_corner, 0>(this->voronoiCell.getEnvelope()) -
         bg::get<bg::min_corner, 0>(this->voronoiCell.getEnvelope());
}

types::coordinate_t VoronoiCellWrapper::getHeight() const {
  return bg::get<bg::max_corner, 1>(this->voronoiCell.getEnvelope()) -
         bg::get<bg::min_corner, 1>(this->voronoiCell.getEnvelope());
}

int VoronoiCellWrapper::getLayer() const { return 0; }

types::graph_vertex_desc_t VoronoiCellWrapper::getVertexDesc() const {
  return this->vertexDesc;
}

bool VoronoiCellWrapper::isTargetable() const { return true; }

bool VoronoiCellWrapper::isSelectable() const { return false; }

void VoronoiCellWrapper::onEntityWrapperTargeted(EntityWrapper *target) {
  // TODO
}

model::VoronoiCell &VoronoiCellWrapper::getVoronoiCell() {
  return this->voronoiCell;
}

const model::VoronoiCell &VoronoiCellWrapper::getVoronoiCell() const {
  return this->voronoiCell;
}

} // namespace ui
} // namespace how
