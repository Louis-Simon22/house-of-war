#ifndef GAMEMANAGERQMLBINDINGS_H
#define GAMEMANAGERQMLBINDINGS_H

#include <memory>

#include <QObject>
#include <QQmlEngine>
#include <QRect>

#include "../control/gamemanager.h"
#include "../model/modeltypes.h"
#include "models/worldmodel.h"

namespace how {
namespace bind {
namespace bg = ::boost::geometry;
class GameManagerQMLBindings : public QObject {
  using GameManager = ::how::control::GameManager;
  using WorldModel = ::how::bind::models::WorldModel;
  using coordinate_t = ::how::model::types::coordinate_t;

  Q_OBJECT
  Q_PROPERTY(WorldModel* worldModel READ getWorldModel CONSTANT)
  Q_PROPERTY(const QRect worldDimensions READ getWorldDimensions CONSTANT)

 public:
  explicit GameManagerQMLBindings(QObject* parent = nullptr);

  Q_INVOKABLE void generateNewWorld(int width, int height);

  WorldModel* getWorldModel() const;
  const QRect getWorldDimensions() const;

 private:
  std::unique_ptr<GameManager> gameManagerPtr;
};
}  // namespace bind
}  // namespace how

#endif  // QMLBINDINGS_H
