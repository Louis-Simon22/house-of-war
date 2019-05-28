#ifndef ENTITYITEM_H
#define ENTITYITEM_H

#include <memory>

#include <QQuickItem>

#include "../../model/entities/graphentity.h"

namespace how {
namespace ui {
class GraphEntityItem : public QQuickItem {
  Q_OBJECT

public:
  GraphEntityItem(QQuickItem *parent,
                  std::shared_ptr<model::GraphEntity> graphEntityPtr);
  virtual ~GraphEntityItem() override = 0;

signals:
  void updateOnGuiThread();
  void updateDimensionsOnGuiThread();
  void mousePressedOnGraphEntityPainter(QMouseEvent *event,
                                        model::GraphEntity *graphEntity);

public slots:
  virtual void updateDimensions() = 0;

public:
  void mousePressEvent(QMouseEvent *event) override;

private:
  void updateAcceptedMouseButtons();

private:
  std::shared_ptr<model::GraphEntity> graphEntityPtr;
};
} // namespace ui
} // namespace how

#endif // ENTITYITEM_H
