#include "polygonoutlinepainter.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

PolygonOutlinePainter::PolygonOutlinePainter(QQuickItem *parent,
                                             std::vector<types::point_t> points)
    : PainterItem(parent), points(points) {}

PolygonOutlinePainter::~PolygonOutlinePainter() {}

// TODO Pulsing outline
// TODO No gaps between outlines
// TODO move this boilerplate code in a parent
// TODO QSGTransformNode as parent of QSGGeometryNode to apply rotations?
QSGNode *PolygonOutlinePainter::updatePaintNode(QSGNode *oldNode,
                                                UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  const int pointsCount = static_cast<int>(this->points.size());

  if (!node) {
    node = new QSGGeometryNode();
    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setDrawingMode(QSGGeometry::DrawLineLoop);
    geometry->setLineWidth(10);
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
  for (std::size_t i = 0; i < points.size(); i++) {
    const auto &point = points[i];
    vertices[i].set(bg::get<0>(point), bg::get<1>(point));
  }
  node->markDirty(QSGNode::DirtyGeometry);

  material->setColor(this->color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

void PolygonOutlinePainter::setColor(QColor color) { this->color = color; }

} // namespace ui
} // namespace how
