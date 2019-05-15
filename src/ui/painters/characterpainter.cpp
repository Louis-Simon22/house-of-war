#include "characterpainter.h"

#include <QColor>
#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

#include <iostream>

namespace how {
namespace ui {

CharacterPainter::CharacterPainter(model::Character &character)
    : EntityPainter(character), character(character) {}

CharacterPainter::~CharacterPainter() {}

QSGNode *CharacterPainter::updatePaintNode(QSGNode *oldNode,
                                           UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;

  const int pointsCount = 4;

  if (!oldNode) {
    node = new QSGGeometryNode();

    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount);
    geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);
  } else {
    node = static_cast<QSGGeometryNode *>(oldNode);
    geometry = node->geometry();
    geometry->allocate(pointsCount);
  }

  const auto &position = this->mapFromItem(
      this->parentItem(),
      QPointF(static_cast<double>(this->character.getPosX()),
              static_cast<double>(this->character.getPosY())));
  const float posX = static_cast<float>(position.x());
  const float posY = static_cast<float>(position.y());
  const float width = this->character.getWidth();
  const float height = this->character.getHeight();
  auto *vertices = geometry->vertexDataAsPoint2D();
  vertices[0].set(posX, posY);
  vertices[1].set(posX + width, posY);
  vertices[2].set(posX + width, posY + height);
  vertices[3].set(posX, posY + height);
  node->markDirty(QSGNode::DirtyGeometry);

  QSGFlatColorMaterial *material =
      static_cast<QSGFlatColorMaterial *>(node->material());
  const QColor color =
      this->character.isSelected() ? Qt::yellow : Qt::red;
  material->setColor(color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

} // namespace ui
} // namespace how
