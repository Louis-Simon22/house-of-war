#include "voronoicellpainter.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

VoronoiCellPainter::VoronoiCellPainter(
    QQuickItem *parent, std::shared_ptr<model::VoronoiCell> voronoiCellPtr)
    : EntityPainter(parent, voronoiCellPtr), voronoiCellPtr(voronoiCellPtr) {
  this->voronoiCellPtr->visualChangedSignal.connect(
      ::boost::bind(&QQuickItem::update, this));
  this->voronoiCellPtr->dimensionsChangedSignal.connect(
      ::boost::bind(&EntityPainter::updateDimensions, this));
  this->updateDimensions();
}

VoronoiCellPainter::~VoronoiCellPainter() {}

void VoronoiCellPainter::updateDimensions() {
  const auto &envelope = voronoiCellPtr->getEnvelope();
  this->setX(static_cast<double>(bg::get<bg::min_corner, 0>(envelope)));
  this->setY(static_cast<double>(bg::get<bg::min_corner, 1>(envelope)));
  this->setZ(static_cast<double>(this->voronoiCellPtr->getLayer()));
  this->setWidth(static_cast<double>(bg::get<bg::max_corner, 0>(envelope) -
                                     bg::get<bg::min_corner, 0>(envelope)));
  this->setHeight(static_cast<double>(bg::get<bg::max_corner, 1>(envelope) -
                                      bg::get<bg::min_corner, 1>(envelope)));
}

// TODO QSGTransformNode as parent of QSGGeometryNode to apply rotations?
QSGNode *VoronoiCellPainter::updatePaintNode(QSGNode *oldNode,
                                             UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  const auto &polygonOuterPoints = this->voronoiCellPtr->getOutlinePoints();
  const int pointsCount = static_cast<int>(polygonOuterPoints.size());

  if (!node) {
    node = new QSGGeometryNode();
    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    material = new QSGFlatColorMaterial();
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);
  } else {
    node = static_cast<QSGGeometryNode *>(oldNode);
    geometry = node->geometry();
    geometry->allocate(pointsCount);
    material = static_cast<QSGFlatColorMaterial *>(node->material());
  }

  auto *vertices = geometry->vertexDataAsPoint2D();
  for (std::size_t i = 0; i < polygonOuterPoints.size(); i++) {
    const auto vertex =
        this->mapFromItem(this->parentItem(), convertF(polygonOuterPoints[i]));
    vertices[i].set(static_cast<float>(vertex.x()),
                    static_cast<float>(vertex.y()));
  }
  node->markDirty(QSGNode::DirtyGeometry);

  const auto altitude = this->voronoiCellPtr->getTile().getAltitude();
  const QColor color = QColor(0, static_cast<int>(altitude * 255),
                              static_cast<int>((1 - altitude) * 255));
  material->setColor(color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

} // namespace ui
} // namespace how
