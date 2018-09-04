#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <memory>
#include "../model/gamemodel.h"
#include "../model/world/worldmodel.h"
#include "../model/world/worldbuilder.h"

using namespace std;

class GameManager : public QObject {
    Q_OBJECT
private:
    unique_ptr<GameModel> gameModelPtr;
    unique_ptr<WorldBuilder> worldBuilder;
    bool shouldCreateNewGame = false;

    Q_PROPERTY(GameModel gameModel READ getGameModel)
    Q_PROPERTY(WorldModel worldModel READ getWorldModel)

public:
    explicit GameManager(QObject *parent = nullptr);
    Q_INVOKABLE void prepareNewGame(int width, int height, int sourcesCount);
    Q_INVOKABLE void instantiateWorld();

    GameModel* getGameModel() const;
    WorldModel* getWorldModel() const;

signals:

public slots:
};

#endif
