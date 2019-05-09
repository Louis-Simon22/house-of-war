#include "voronoicellpainter.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

namespace how {
namespace ui {

VoronoiCellPainter::VoronoiCellPainter(const model::VoronoiCell &voronoiCell)
    : EntityPainter(), voronoiCell(voronoiCell) {
}

VoronoiCellPainter::~VoronoiCellPainter() {}

// TODO QSGTransformNode as parent of QSGGeometryNode to apply rotations?
QSGNode *VoronoiCellPainter::updatePaintNode(QSGNode *oldNode,
                                             UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;

  const auto &polygonOuterPoints = this->voronoiCell.getOutlinePoints();
  const int pointsCount = static_cast<int>(polygonOuterPoints.size());

  if (!node) {
    node = new QSGGeometryNode();
    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);
  } else {
    node = static_cast<QSGGeometryNode *>(oldNode);
    geometry = node->geometry();
    geometry->allocate(pointsCount);
  }

  auto *vertices = geometry->vertexDataAsPoint2D();
  for (std::size_t i = 0; i < polygonOuterPoints.size(); i++) {
    const auto &vertex =
        this->mapFromItem(this->parentItem(), convertF(polygonOuterPoints[i]));
    vertices[i].set(static_cast<float>(vertex.x()),
                    static_cast<float>(vertex.y()));
  }

  QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
  material->setColor(
      QColor(0, static_cast<int>(voronoiCell.getTile().getHeight() * 255),
             static_cast<int>((1 - voronoiCell.getTile().getHeight()) * 255)));

  node->setMaterial(material);
  node->setFlag(QSGNode::OwnsMaterial);

  node->markDirty(QSGNode::DirtyGeometry);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

} // namespace ui
} // namespace how
