#ifndef GAMEDATAMANAGERQMLWRAPPER_H
#define GAMEDATAMANAGERQMLWRAPPER_H

#include <QObject>
#include <memory>

#include "../../model/gamedatamanager.h"
#include "../control/characterscontroller.h"
#include "../control/modelthreadmanager.h"
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
  Q_PROPERTY(CharactersController *charactersController READ
                 getCharactersController NOTIFY newGameGenerated)

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
  CharactersController *getCharactersController();

private:
  ModelThreadManager modelThreadManager;
  model::GameDataManager gameDataManager;
};
} // namespace ui
} // namespace how

#endif // GAMEDATAMANAGERQMLBINDINGS_H
