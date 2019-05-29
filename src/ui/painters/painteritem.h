#ifndef GRAPHENTITYPAINTER_H
#define GRAPHENTITYPAINTER_H

#include <QQuickItem>

namespace how {
namespace ui {
class PainterItem : public QQuickItem {
  Q_OBJECT

public:
  PainterItem(QQuickItem *parent);
  virtual ~PainterItem() override = 0;

signals:
  void updateOnGuiThread();
};
} // namespace ui
} // namespace how

#endif // GRAPHENTITYPAINTER_H
