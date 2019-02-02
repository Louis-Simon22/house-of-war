#ifndef GAMEMANAGERQMLBINDINGS_H
#define GAMEMANAGERQMLBINDINGS_H

#include <memory>

#include <QList>
#include <QObject>
#include <QPoint>
#include <QQmlEngine>
#include <QRect>
#include <QVariant>

#include "../control/gamemanager.h"
#include "../model/modeltypes.h"
#include "./models/worldmodel.h"

namespace how {
namespace bind {
namespace bg = ::boost::geometry;
namespace {
using GameManager = ::how::control::GameManager;
using WorldModel = ::how::bind::WorldModel;
using coordinate_t = ::how::model::types::coordinate_t;
} // namespace
class GameManagerQMLBindings : public QObject {

  Q_OBJECT
  Q_PROPERTY(WorldModel *worldModel READ getWorldModel CONSTANT)
  Q_PROPERTY(
      const QList<QVariant> outlineSegments READ getOutlineSegments CONSTANT)
  Q_PROPERTY(const QList<QVariant> pathSegments READ getPathSegments CONSTANT)
  Q_PROPERTY(const QRect worldBounds READ getWorldBounds CONSTANT)

public:
  explicit GameManagerQMLBindings(QObject *parent = nullptr);

  Q_INVOKABLE void generateNewWorld(int width, int height);

  WorldModel *getWorldModel() const;
  const QList<QVariant> getOutlineSegments() const;
  const QList<QVariant> getPathSegments() const;
  const QRect getWorldBounds() const;

private:
  std::unique_ptr<GameManager> gameManagerPtr;

  const QList<QVariant>
  convert(const std::vector<model::types::segment_t> *segments) const;
};
} // namespace bind
} // namespace how

#endif // QMLBINDINGS_H
