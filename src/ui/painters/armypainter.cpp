#include "armypainter.h"

#include <math.h>

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

namespace how {
namespace ui {

ArmyPainter::ArmyPainter(QQuickItem *parent,
                         std::shared_ptr<model::Army> armyPtr)
    : PainterItem(parent, armyPtr), armyPtr(armyPtr) {
  this->updateDimensions();
}

ArmyPainter::~ArmyPainter() {}

void ArmyPainter::updateDimensions() {
  const auto detectionRange = this->armyPtr->getDetectionRadius();
  this->setX(static_cast<double>(this->armyPtr->getPosX() - detectionRange));
  this->setY(static_cast<double>(this->armyPtr->getPosY() - detectionRange));
  this->setZ(static_cast<double>(this->armyPtr->getLayer()));
  this->setWidth(static_cast<double>(detectionRange * 2));
  this->setHeight(static_cast<double>(detectionRange * 2));
}

QSGNode *ArmyPainter::updatePaintNode(QSGNode *oldNode,
                                      QQuickItem::UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;
  QSGFlatColorMaterial *material = nullptr;

  constexpr int pointsCount = 20;
  // One vertex for the center of the fan and one for the first point again
  constexpr int vertexCount = pointsCount + 2;

  if (!oldNode) {
    node = new QSGGeometryNode();

    geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), vertexCount);
    geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
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

  const auto detectionRange = this->armyPtr->getDetectionRadius();
  auto *vertices = geometry->vertexDataAsPoint2D();
  auto center = detectionRange;
  auto radius = detectionRange;
  auto angleStep = static_cast<float>(2 * M_PI / pointsCount);
  vertices[0].set(center, center);
  for (std::size_t i = 0; i < pointsCount + 1; i++) {
    const auto angle = i * angleStep;
    vertices[i + 1].set(center + radius * cos(angle),
                        center + radius * sin(angle));
  }
  node->markDirty(QSGNode::DirtyGeometry);

  const QColor color = this->armyPtr->isSelected() ? Qt::yellow : Qt::red;
  material->setColor(color);
  node->markDirty(QSGNode::DirtyMaterial);

  return node;
}

} // namespace ui
} // namespace how
