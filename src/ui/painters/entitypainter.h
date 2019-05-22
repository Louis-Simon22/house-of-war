#ifndef GRAPHENTITYPAINTER_H
#define GRAPHENTITYPAINTER_H

#include <memory>

#include <QQuickItem>

#include "../../model/entities/graphentity.h"

namespace how {
namespace ui {
class EntityPainter : public QQuickItem {
  Q_OBJECT

public:
  EntityPainter(QQuickItem *parent,
                std::shared_ptr<model::GraphEntity> graphEntityPtr);
  virtual ~EntityPainter() override = 0;

signals:
  void mousePressedOnGraphEntityPainter(
      QMouseEvent *event, std::shared_ptr<model::GraphEntity> graphEntityPtr);

public slots:
  virtual void updateDimensions() = 0;

public:
  void mousePressEvent(QMouseEvent *event) override;

private:
  void updateAcceptedMouseButtons();

private:
  std::shared_ptr<model::GraphEntity> graphEntityPtr;

public:
  std::size_t index;
};
} // namespace ui
} // namespace how

#endif // GRAPHENTITYPAINTER_H
