#ifndef GRAPHENTITYPAINTER_H
#define GRAPHENTITYPAINTER_H

#include <memory>

#include <QQuickItem>

#include "../../model/entities/graphentity.h"

namespace how {
namespace ui {
class PainterItem : public QQuickItem {
  Q_OBJECT

public:
  PainterItem(QQuickItem *parent);
  virtual ~PainterItem() override = 0;
};
} // namespace ui
} // namespace how

#endif // GRAPHENTITYPAINTER_H
