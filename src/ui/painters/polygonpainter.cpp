#include "polygonpainter.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

PolygonPainter::PolygonPainter(QQuickItem *parent)
    : PainterItem(parent), points() {}

PolygonPainter::~PolygonPainter() {}

// TODO QSGTransformNode as parent of QSGGeometryNode to apply rotations?
QSGNode *PolygonPainter::updatePaintNode(QSGNode *oldNode,
                                         UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  const int pointsCount = static_cast<int>(this->points.size());

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
  for (std::size_t i = 0; i < this->points.size(); i += 2) {
    vertices[i].set(this->points[i], this->points[i + 1]);
  }
  node->markDirty(QSGNode::DirtyGeometry);

  material->setColor(this->color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

void PolygonPainter::setPoints(std::vector<float> points) {
  this->points = points;
  this->update();
}

void PolygonPainter::setColor(QColor color) {
  this->color = color;
  this->update();
}

} // namespace ui
} // namespace how
