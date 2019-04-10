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
    const int pointsCount = static_cast<int>(polygonOuterPoints.size() + 1);

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

    const auto &itemPos = this->position();
    auto *vertices = geometry->vertexDataAsPoint2D();
    // First vertex is the center of the triangle fan
    const auto &center = scopePoint(itemPos, voronoiCell->centroid);
    vertices[0].set(static_cast<float>(center.x()),
                    static_cast<float>(center.y()));

    std::cout << itemPos.x() << "|" << itemPos.y() << std::endl;
    std::cout << vertices[0].x << "|" << vertices[0].y << std::endl;
    for (std::size_t i = 1; i < static_cast<std::size_t>(pointsCount); i++) {
      const auto &vertex = this->mapFromGlobal(convertF(polygonOuterPoints[i]));
      vertices[i].set(static_cast<float>(vertex.x()),
                      static_cast<float>(vertex.y()));
      std::cout << vertices[i].x << "|" << vertices[i].y << std::endl;
    }
    std::cout << "=======" << std::endl;

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
    material->setColor(
        QColor(static_cast<int>(voronoiCell->cellData.elevation * 255), 0, 0));
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
