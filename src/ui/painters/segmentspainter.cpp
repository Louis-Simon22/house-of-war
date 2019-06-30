#include "segmentspainter.h"

#include <QColor>
#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>
#include <QSGNode>

#include <iostream>

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

SegmentsPainter::SegmentsPainter(const std::vector<types::segment_t> &segments,
                                 QQuickItem *parent)
    : QQuickItem(parent), segments(segments) {
  this->setAntialiasing(true);
  this->setFlag(QQuickItem::ItemHasContents, true);
  this->setX(parent->x());
  this->setY(parent->y());
  this->setZ(static_cast<double>(model::Layers::MAP_ELEMENTS));
  this->setWidth(parent->width());
  this->setHeight(parent->height());
}

QSGNode *SegmentsPainter::updatePaintNode(QSGNode *oldNode,
                                          QQuickItem::UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;

  const int pointsCount = static_cast<int>(this->segments.size()) * 2;

  if (!oldNode) {
    node = new QSGGeometryNode();

    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setDrawingMode(QSGGeometry::DrawLines);
    geometry->setLineWidth(3);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
    material->setColor(Qt::black);
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);
  } else {
    node = static_cast<QSGGeometryNode *>(oldNode);
    geometry = node->geometry();
    geometry->allocate(pointsCount);
  }

  auto *vertices = geometry->vertexDataAsPoint2D();
  for (std::size_t i = 0; i < this->segments.size(); i++) {
    const auto &segment = this->segments[i];
    const float posX1 = bg::get<0, 0>(segment);
    const float posY1 = bg::get<0, 1>(segment);
    const float posX2 = bg::get<1, 0>(segment);
    const float posY2 = bg::get<1, 1>(segment);
    const auto verticesIndex = i * 2;
    vertices[verticesIndex].set(posX1, posY1);
    vertices[verticesIndex + 1].set(posX2, posY2);
  }

  return node;
}
} // namespace ui
} // namespace how
