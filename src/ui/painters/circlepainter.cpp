#include "circlepainter.h"

#include <math.h>

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

namespace how {
namespace ui {

CirclePainter::CirclePainter(QQuickItem *parent, float lineWidth, QColor color)
    : PainterItem(parent), lineWidth(lineWidth), color(color) {}

CirclePainter::~CirclePainter() {}

QSGNode *CirclePainter::updatePaintNode(QSGNode *oldNode,
                                        QQuickItem::UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  constexpr int pointsCount = 20;
  // One extra vertex to close the circle
  constexpr int vertexCount = pointsCount + 1;

  if (!oldNode) {
    node = new QSGGeometryNode();

    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), vertexCount);
    geometry->setDrawingMode(QSGGeometry::DrawLines);
    geometry->setLineWidth(this->lineWidth);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    material = new QSGFlatColorMaterial();
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);
  } else {
    node = static_cast<QSGGeometryNode *>(oldNode);
    geometry = node->geometry();
    geometry->allocate(vertexCount);
    material = static_cast<QSGFlatColorMaterial *>(node->material());
  }

  auto radius = static_cast<float>(this->width() / 2);
  auto *vertices = geometry->vertexDataAsPoint2D();
  auto center = radius;
  auto angleStep = static_cast<float>(2 * M_PI / pointsCount);
  for (std::size_t i = 0; i < vertexCount; i++) {
    const auto angle = i * angleStep;
    vertices[i].set(center + radius * cos(angle), center + radius * sin(angle));
  }
  node->markDirty(QSGNode::DirtyGeometry);

  material->setColor(this->color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

void CirclePainter::setLineWidth(float lineWidth) {
  this->lineWidth = lineWidth;
  this->update();
}

void CirclePainter::setColor(QColor color) {
  this->color = color;
  this->update();
}

} // namespace ui
} // namespace how
