#ifndef GRAPHENTITYPAINTER_H
#define GRAPHENTITYPAINTER_H

#include <QQuickItem>

#include "../../model/entities/graphentity.h"

namespace how {
namespace ui {
class EntityPainter : public QQuickItem {
  Q_OBJECT

public:
  EntityPainter(model::GraphEntity &graphEntity, QQuickItem *parent = nullptr);
  virtual ~EntityPainter() = 0;

public slots:
  void updateDimensions();

public:
  model::GraphEntity &getGraphEntity();

private:
  model::GraphEntity &graphEntity;
};
} // namespace ui
} // namespace how

#endif // GRAPHENTITYPAINTER_H
