#include "polygonpainter.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

PolygonPainter::PolygonPainter(std::vector<types::point_t> points,
                               QQuickItem *parent)
    : PainterItem(parent), points(points) {}

PolygonPainter::~PolygonPainter() {}

QSGNode *PolygonPainter::updatePaintNode(QSGNode *oldNode,
                                         UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  int pointsCount = this->points.size();

  if (!oldNode) {
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
  for (std::size_t i = 0; i < this->points.size(); i++) {
    const auto &point = this->points[i];
    vertices[i].set(bg::get<0>(point), bg::get<1>(point));
  }
  node->markDirty(QSGNode::DirtyGeometry);

  material->setColor(this->color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

void PolygonPainter::setColor(QColor color) {
  this->color = color;
  this->update();
}

} // namespace ui
} // namespace how
