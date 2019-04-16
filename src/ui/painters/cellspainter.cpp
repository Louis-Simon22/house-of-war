#include "cellspainter.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "../conversion/converter.h"

#include <iostream>

namespace how {
namespace ui {
CellsPainter::CellsPainter(QQuickItem *parent)
    : QQuickItem(parent), worldDataQMLWrapperPtr(nullptr), cellIndex(-1) {
  this->setAntialiasing(true);
  this->setFlag(QQuickItem::ItemHasContents, true);
}

QSGNode *CellsPainter::updatePaintNode(QSGNode *oldNode,
                                       UpdatePaintNodeData *) {
  QSGGeometryNode *node = nullptr;
  QSGGeometry *geometry = nullptr;

  if (this->worldDataQMLWrapperPtr && this->cellIndex >= 0) {
    const auto *voronoiCell =
        this->worldDataQMLWrapperPtr->getVoronoiCellAt(this->cellIndex);
    const auto &polygonOuterPoints = voronoiCell->outlinePoints;
    const int pointsCount = static_cast<int>(polygonOuterPoints.size());

    if (!node) {
      node = new QSGGeometryNode();
      geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
                                 pointsCount);
      geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
      node->setGeometry(geometry);
      node->setFlag(QSGNode::OwnsGeometry);
    } else {
      node = static_cast<QSGGeometryNode *>(oldNode);
      geometry = node->geometry();
      geometry->allocate(pointsCount);
    }

    auto *vertices = geometry->vertexDataAsPoint2D();
    for (std::size_t i = 0; i < polygonOuterPoints.size(); i++) {
      const auto &vertex = this->mapFromItem(this->parentItem(),
                                             convertF(polygonOuterPoints[i]));
      vertices[i].set(static_cast<float>(vertex.x()),
                      static_cast<float>(vertex.y()));
    }

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
    if (voronoiCell->cellData.elevation > 0.0F) {
      material->setColor(QColor(
          0, 0, static_cast<int>(voronoiCell->cellData.elevation * 255)));
    } else {
      material->setColor(QColor(
          0, static_cast<int>(voronoiCell->cellData.elevation * -255),
          0));
    }
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    node->markDirty(QSGNode::DirtyGeometry);
    node->markDirty(QSGNode::DirtyMaterial);
  }

  return node;
}

void CellsPainter::setWorldDataQMLWrapper(
    WorldDataQMLWrapper *worldDataQMLWrapperPtr) {
  this->worldDataQMLWrapperPtr = worldDataQMLWrapperPtr;
  this->update();
}

void CellsPainter::setCellIndex(int index) {
  this->cellIndex = index;
  this->update();
}
} // namespace ui
} // namespace how
