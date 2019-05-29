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
  GraphEntityItem(std::shared_ptr<model::GraphEntity> graphEntityPtr,
                  QQuickItem *visualParent, QObject *memoryParent = nullptr);
  virtual ~GraphEntityItem() override = 0;

signals:
  void updateOnGuiThread();
  void mousePressedOnGraphEntityPainter(QMouseEvent *event,
                                        model::GraphEntity *graphEntity);

private slots:
  virtual void onGraphEntityUpdated() = 0;

public:
  void mousePressEvent(QMouseEvent *event) override;

public:
  void setParents(QQuickItem *visualParent, QObject *memoryParent);

private:
  void updateAcceptedMouseButtons();

private:
  std::shared_ptr<model::GraphEntity> graphEntityPtr;
};
} // namespace ui
} // namespace how

#endif // ENTITYITEM_H
