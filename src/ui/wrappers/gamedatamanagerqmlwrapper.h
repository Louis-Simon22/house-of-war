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
                 newGameGenerated FINAL)
  Q_PROPERTY(CharacterDataQMLWrapper *characterData READ
                 getCharacterDataQMLWrapper NOTIFY newGameGenerated FINAL)
  Q_PROPERTY(CharactersController *charactersController READ
                 getCharactersController NOTIFY newGameGenerated FINAL)

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
  model::GameDataManager gameDataManager;
  ModelThreadManager modelThreadManager;
  std::unique_ptr<WorldDataQMLWrapper> worldDataQMLWrapperPtr;
  std::unique_ptr<CharacterDataQMLWrapper> characterDataQMLWrapperPtr;
  std::unique_ptr<CharactersController> charactersControllerPtr;
};
} // namespace ui
} // namespace how

#endif // GAMEDATAMANAGERQMLBINDINGS_H
