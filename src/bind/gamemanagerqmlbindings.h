#ifndef GAMEMANAGERQMLBINDINGS_H
#define GAMEMANAGERQMLBINDINGS_H

#include <memory>

#include <QObject>
#include <QQmlEngine>
#include <QRect>

#include "../control/gamemanager.h"
#include "../model/modeltypes.h"
#include "./models/edgesmodel.h"
#include "./models/worldmodel.h"

namespace how {
namespace bind {
namespace bg = ::boost::geometry;
namespace {
using GameManager = ::how::control::GameManager;
using WorldModel = ::how::bind::models::WorldModel;
using EdgesModel = ::how::bind::models::EdgesModel;
using coordinate_t = ::how::model::types::coordinate_t;
} // namespace
class GameManagerQMLBindings : public QObject {

  Q_OBJECT
  Q_PROPERTY(WorldModel *worldModel READ getWorldModel CONSTANT)
  Q_PROPERTY(EdgesModel *edgesModel READ getEdgesModel CONSTANT)
  Q_PROPERTY(const QRect worldDimensions READ getWorldDimensions CONSTANT)

public:
  explicit GameManagerQMLBindings(QObject *parent = nullptr);

  Q_INVOKABLE void generateNewWorld(int width, int height);

  WorldModel *getWorldModel() const;
  EdgesModel *getEdgesModel() const;
  const QRect getWorldDimensions() const;

private:
  std::unique_ptr<GameManager> gameManagerPtr;
};
} // namespace bind
} // namespace how

#endif // QMLBINDINGS_H
