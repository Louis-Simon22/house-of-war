#ifndef GRAPHENTITYPAINTER_H
#define GRAPHENTITYPAINTER_H

#include <QQuickItem>

namespace how {
namespace ui {
class EntityPainter : public QQuickItem {
  Q_OBJECT

public:
  EntityPainter(QQuickItem *parent = nullptr);
  virtual ~EntityPainter() = 0;

};
} // namespace ui
} // namespace how

#endif // GRAPHENTITYPAINTER_H
