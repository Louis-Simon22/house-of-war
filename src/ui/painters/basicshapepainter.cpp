#include "basicshapepainter.h"

#include <QSGFlatColorMaterial>

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

BasicShapePainter::BasicShapePainter(QQuickItem *parent,
                                     QSGGeometry::DrawingMode drawingMode,
                                     QColor color,
                                     std::vector<types::point_t> points,
                                     float lineWidth)
    : PainterItem(parent), points(points), pointsChanged(true), color(color),
      drawingMode(drawingMode), lineWidth(lineWidth) {}

BasicShapePainter::~BasicShapePainter() {}

// TODO Pulsing selection outline
// TODO No gaps between outlines
QSGNode *BasicShapePainter::updatePaintNode(QSGNode *oldNode,
                                            UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  const int pointsCount = static_cast<int>(this->points.size());

  if (oldNode) {
    node = static_cast<QSGGeometryNode *>(oldNode);
    geometry = node->geometry();
    material = static_cast<QSGFlatColorMaterial *>(node->material());
  } else {
    node = new QSGGeometryNode();
    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setLineWidth(this->lineWidth);
    geometry->setDrawingMode(this->drawingMode);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    material = new QSGFlatColorMaterial();
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);
  }

  if (pointsChanged) {
    geometry->allocate(pointsCount);
    auto *vertices = geometry->vertexDataAsPoint2D();
    for (std::size_t i = 0; i < points.size(); i++) {
      const auto &point = points[i];
      // TODO path points are absolute. Maybe make it have its own object
      vertices[i].set(bg::get<0>(point), bg::get<1>(point));
    }
    this->pointsChanged = false;
    node->markDirty(QSGNode::DirtyGeometry);
  }

  material->setColor(this->color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

void BasicShapePainter::setColor(QColor color) {
  this->color = color;
  this->update();
}

void BasicShapePainter::setPoints(std::vector<types::point_t> points) {
  this->points = points;
  this->pointsChanged = true;
  this->update();
}

void BasicShapePainter::clearPoints() {
  this->points.clear();
  this->pointsChanged = true;
  this->update();
}

void BasicShapePainter::setLineWidth(float lineWidth) {
  this->lineWidth = lineWidth;
  this->update();
}

} // namespace ui
} // namespace how
