#ifndef GAMEDATAMANAGERQMLWRAPPER_H
#define GAMEDATAMANAGERQMLWRAPPER_H

#include <QObject>
#include <QQuickItem>
#include <QRect>

#include "../../model/managers/worldmanager.h"

namespace how {
namespace ui {
class WorldManagerWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(QRect worldBounds READ getWorldBounds CONSTANT FINAL)

public:
  WorldManagerWrapper(model::WorldManager *worldManagerPtr);

public:
  const model::WorldManager *getWorldManager() const;

private:
  QRect getWorldBounds() const;

private:
  model::WorldManager *worldManagerPtr;
};
} // namespace ui
} // namespace how

#endif // GAMEDATAMANAGERQMLBINDINGS_H
