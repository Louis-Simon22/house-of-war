#ifndef QMLBINDINGS_H
#define QMLBINDINGS_H

#include <QObject>
#include <QRect>
#include <memory>

#include "../control/gamemanager.h"
#include "../model/modeltypes.h"
#include "models/worldmodel.h"

namespace how {
namespace bind {
namespace bg = ::boost::geometry;
class GameManagerQMLBindings : public QObject {
  using GameManager = ::how::control::GameManager;

  Q_OBJECT
  Q_PROPERTY(const models::WorldModel* worldModel READ getWorldModel CONSTANT)
  Q_PROPERTY(const QRect worldDimensions READ getWorldDimensions CONSTANT)

 public:
  explicit GameManagerQMLBindings(QObject* parent = nullptr);

  Q_INVOKABLE void generateNewWorld(
      ::how::model::types::WorldGenerationConfig config);

  const models::WorldModel* getWorldModel() const;
  const QRect getWorldDimensions() const;

 private:
  std::unique_ptr<models::WorldModel> worldModelPtr;
  std::unique_ptr<GameManager> gameManagerPtr;
};
}  // namespace bind
}  // namespace how

#endif  // QMLBINDINGS_H
