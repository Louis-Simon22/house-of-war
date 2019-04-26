#ifndef GAMEDATAMANAGERQMLWRAPPER_H
#define GAMEDATAMANAGERQMLWRAPPER_H

#include <QObject>
#include <memory>

#include "../../model/managers/modelmanager.h"
#include "../control/characterscontroller.h"
#include "../control/modelthreadmanager.h"
#include "./graphentitymanagerqmlwrapper.h"
#include "./worldmanagerqmlwrapper.h"

namespace how {
namespace ui {
class ModelManagerQMLWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(WorldManagerQMLWrapper *worldManager READ getWorldManagerQMLWrapper
                 NOTIFY newGameGenerated FINAL)
  Q_PROPERTY(GraphEntityManagerQMLWrapper *graphEntityManager READ
                 getGraphEntityManagerQMLWrapper NOTIFY newGameGenerated FINAL)
  Q_PROPERTY(CharactersController *charactersController READ
                 getCharactersController NOTIFY newGameGenerated FINAL)

public:
  ModelManagerQMLWrapper(QObject *parent = nullptr);

signals:
  void newGameGenerated();

public slots:
  void newGame(int width, int height, float minimumVoronoiCellDistance,
               int randomSeed);
  void loadGame();

public:
  WorldManagerQMLWrapper *getWorldManagerQMLWrapper() const;
  GraphEntityManagerQMLWrapper *getGraphEntityManagerQMLWrapper() const;
  CharactersController *getCharactersController();

private:
  model::ModelManager modelManager;
  ModelThreadManager modelThreadManager;
  std::unique_ptr<WorldManagerQMLWrapper> WorldManagerQMLWrapperPtr;
  std::unique_ptr<GraphEntityManagerQMLWrapper> graphEntityManagerQMLWrapper;
  std::unique_ptr<CharactersController> charactersControllerPtr;
};
} // namespace ui
} // namespace how

#endif // GAMEDATAMANAGERQMLBINDINGS_H
