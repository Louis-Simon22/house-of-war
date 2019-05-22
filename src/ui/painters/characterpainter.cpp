#include "characterpainter.h"

#include <QColor>
#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>
#include <QSGNode>

#include "../conversion/converter.h"

#include <iostream>

namespace how {
namespace ui {

CharacterPainter::CharacterPainter(
    QQuickItem *parent, std::shared_ptr<model::Character> characterPtr)
    : EntityPainter(parent, characterPtr), characterPtr(characterPtr) {
  this->characterPtr->visualChangedSignal.connect(
      ::boost::bind(&QQuickItem::update, this));
  this->characterPtr->dimensionsChangedSignal.connect(
      ::boost::bind(&EntityPainter::updateDimensions, this));
  this->updateDimensions();
}

CharacterPainter::~CharacterPainter() {}

void CharacterPainter::updateDimensions() {
  this->setX(
      static_cast<double>(this->characterPtr->getPosX() - CHARACTER_WIDTH / 2));
  this->setY(
      static_cast<double>(this->characterPtr->getPosY() - CHARACTER_WIDTH / 2));
  this->setZ(static_cast<double>(this->characterPtr->getLayer()));
  this->setWidth(static_cast<double>(CHARACTER_WIDTH * 2));
  this->setHeight(static_cast<double>(CHARACTER_WIDTH * 2));
}

QSGNode *CharacterPainter::updatePaintNode(QSGNode *oldNode,
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
  vertices[1].set(CHARACTER_WIDTH, 0);
  vertices[2].set(CHARACTER_WIDTH, CHARACTER_WIDTH);
  vertices[3].set(0, CHARACTER_WIDTH);
  node->markDirty(QSGNode::DirtyGeometry);

  const QColor color = this->characterPtr->isSelected() ? Qt::yellow : Qt::red;
  material->setColor(color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

} // namespace ui
} // namespace how
