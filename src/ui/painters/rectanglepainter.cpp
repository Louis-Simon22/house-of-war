#include "rectanglepainter.h"

#include <QColor>
#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

namespace how {
namespace ui {

RectanglePainter::RectanglePainter(float width, float height,
                                   QQuickItem *parent)
    : PainterItem(parent), width(width), height(height) {}

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
  auto halfwidth = this->width / 2;
  auto halfheight = this->height / 2;
  vertices[0].set(-halfwidth, -halfheight);
  vertices[1].set(halfwidth, -halfheight);
  vertices[2].set(halfwidth, halfheight);
  vertices[3].set(-halfwidth, halfheight);
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
