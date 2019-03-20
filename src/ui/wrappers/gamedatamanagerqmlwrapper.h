#ifndef GAMEDATAMANAGERQMLWRAPPER_H
#define GAMEDATAMANAGERQMLWRAPPER_H

#include <QObject>
#include <memory>

#include "../../model/gamedatamanager.h"
#include "./characterdataqmlwrapper.h"
#include "./worlddataqmlwrapper.h"

namespace how {
namespace ui {
class GameDataManagerQMLWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(WorldDataQMLWrapper *worldData READ getWorldDataQMLWrapper NOTIFY
                 newGameGenerated)
  Q_PROPERTY(CharacterDataQMLWrapper *characterData READ
                 getCharacterDataQMLWrapper NOTIFY newGameGenerated)

public:
  GameDataManagerQMLWrapper(QObject *parent = nullptr);

signals:
  void newGameGenerated();

public slots:
  void newGame(int width, int height);
  void loadGame();

public:
  WorldDataQMLWrapper *getWorldDataQMLWrapper() const;
  CharacterDataQMLWrapper *getCharacterDataQMLWrapper() const;

private:
  std::unique_ptr<model::GameDataManager> gameDataManagerPtr;
};
} // namespace ui
} // namespace how

#endif // GAMEDATAMANAGERQMLBINDINGS_H
