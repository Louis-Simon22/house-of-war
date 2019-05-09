#include "voronoicellwrapper.h"

#include "../painters/voronoicellpainter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

VoronoiCellWrapper::VoronoiCellWrapper(model::VoronoiCell &voronoiCell)
    : voronoiCell(voronoiCell) {}

VoronoiCellWrapper::~VoronoiCellWrapper() {}

EntityPainter *VoronoiCellWrapper::createEntityPainter() const {
  return new VoronoiCellPainter(this->voronoiCell);
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

bool VoronoiCellWrapper::isTargetable() const { return true; }

bool VoronoiCellWrapper::isSelectable() const { return false; }

} // namespace ui
} // namespace how
