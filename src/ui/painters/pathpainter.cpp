#include "pathpainter.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>
#include <QSGNode>

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

PathPainter::PathPainter(std::vector<types::point_t> points, QQuickItem *parent)
    : PainterItem(parent), points(points) {}

PathPainter::~PathPainter() {}

QSGNode *PathPainter::updatePaintNode(QSGNode *oldNode,
                                      QQuickItem::UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  int pointsCount = this->points.size();

  if (!oldNode) {
    node = new QSGGeometryNode();

    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setDrawingMode(QSGGeometry::DrawLines);
    geometry->setLineWidth(4);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    material = new QSGFlatColorMaterial();
    material->setColor(Qt::red);
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

void PathPainter::setPoints(std::vector<types::point_t> points) {
  this->points = points;
}

} // namespace ui
} // namespace how
