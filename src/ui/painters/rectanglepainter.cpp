#include "rectanglepainter.h"

#include <QColor>
#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>
#include <QSGNode>

#include "../conversion/converter.h"

#include <iostream>

namespace how {
namespace ui {

RectanglePainter::RectanglePainter(QQuickItem *parent, QColor color)
    : PainterItem(parent), color(color) {}

RectanglePainter::~RectanglePainter() {}

QSGNode *RectanglePainter::updatePaintNode(QSGNode *oldNode,
                                           UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  constexpr int pointsCount = 4;

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
  vertices[0].set(0, 0);
  vertices[1].set(static_cast<float>(this->width()), 0);
  vertices[2].set(static_cast<float>(this->width()),
                  static_cast<float>(this->height()));
  vertices[3].set(0, static_cast<float>(this->height()));
  node->markDirty(QSGNode::DirtyGeometry);

  material->setColor(this->color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

void RectanglePainter::setColor(QColor color) {
  this->color = color;
  this->update();
}

} // namespace ui
} // namespace how
