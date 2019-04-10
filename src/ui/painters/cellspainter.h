#ifndef CELLSPAINTER_H
#define CELLSPAINTER_H

#include <QQuickItem>

#include "../wrappers/worlddataqmlwrapper.h"

namespace how {
namespace ui {
class CellsPainter : public QQuickItem {
  Q_OBJECT
  Q_PROPERTY(WorldDataQMLWrapper *worldData MEMBER worldDataQMLWrapperPtr WRITE
                 setWorldDataQMLWrapper FINAL)
  Q_PROPERTY(int cellIndex MEMBER cellIndex WRITE setCellIndex FINAL)

public:
  CellsPainter(QQuickItem *parent = nullptr);

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  void setWorldDataQMLWrapper(WorldDataQMLWrapper *worldDataPtr);
  void setCellIndex(int index);

private:
  WorldDataQMLWrapper *worldDataQMLWrapperPtr;
  int cellIndex;
};
} // namespace ui
} // namespace how

#endif // CELLSPAINTER_H
