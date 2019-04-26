#ifndef TilePainter_H
#define TilePainter_H

#include <QQuickItem>

#include "../wrappers/worldmanagerqmlwrapper.h"

namespace how {
namespace ui {
class TilePainter : public QQuickItem {
  Q_OBJECT
  Q_PROPERTY(
      WorldManagerQMLWrapper *worldManager MEMBER worldManagerQMLWrapperPtr
          WRITE setWorldManagerQMLWrapper FINAL)
  Q_PROPERTY(int cellIndex MEMBER cellIndex WRITE setCellIndex FINAL)

public:
  TilePainter(QQuickItem *parent = nullptr);

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  void
  setWorldManagerQMLWrapper(WorldManagerQMLWrapper *worldManagerQMLWrapperPtr);
  void setCellIndex(int index);

private:
  WorldManagerQMLWrapper *worldManagerQMLWrapperPtr;
  int cellIndex;
};
} // namespace ui
} // namespace how

#endif // TilePainter_H
