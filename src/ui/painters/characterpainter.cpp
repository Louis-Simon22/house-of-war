#include "characterpainter.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

namespace how {
namespace ui {

CharacterPainter::CharacterPainter(const model::Character &character)
    : character(character) {}

CharacterPainter::~CharacterPainter() {}

QSGNode *CharacterPainter::updatePaintNode(QSGNode *oldNode,
                                           UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;

  const auto &position = this->character.getPosition();
  const float halfwidth = 5;
  const int pointsCount = 4;

  if (!node) {
    node = new QSGGeometryNode();
    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);
  } else {
    node = static_cast<QSGGeometryNode *>(oldNode);
    geometry = node->geometry();
    geometry->allocate(pointsCount);
  }

  auto *vertices = geometry->vertexDataAsPoint2D();
  const auto &center =
      this->mapFromItem(this->parentItem(), convertF(position));
  const auto centerX = static_cast<float>(center.x());
  const auto centerY = static_cast<float>(center.y());
  vertices[0].set(centerX - halfwidth, centerY - halfwidth);
  vertices[1].set(centerX + halfwidth, centerY - halfwidth);
  vertices[2].set(centerX + halfwidth, centerY + halfwidth);
  vertices[3].set(centerX - halfwidth, centerY + halfwidth);

  QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
  material->setColor(Qt::yellow);

  node->setMaterial(material);
  node->setFlag(QSGNode::OwnsMaterial);

  node->markDirty(QSGNode::DirtyGeometry);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

} // namespace ui
} // namespace how
