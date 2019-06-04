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

  const int pointsCount = 50 + static_cast<int>(this->radius) * 2;

  if (!oldNode) {
    node = new QSGGeometryNode();

    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setDrawingMode(QSGGeometry::DrawLineLoop);
    geometry->setLineWidth(this->lineWidth);
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
  auto angleStep = static_cast<float>(2 * M_PI / pointsCount);
  for (std::size_t i = 0; i < static_cast<std::size_t>(pointsCount); i++) {
    const auto angle = i * angleStep;
    vertices[i].set(this->radius * cos(angle), this->radius * sin(angle));
  }
  node->markDirty(QSGNode::DirtyGeometry);

  material->setColor(this->color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

void CirclePainter::setLineWidth(float lineWidth) {
  this->lineWidth = lineWidth;
}

void CirclePainter::setColor(QColor color) { this->color = color; }

void CirclePainter::setRadius(float radius) { this->radius = radius; }

} // namespace ui
} // namespace how
