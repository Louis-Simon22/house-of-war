#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <memory>
#include <QRect>
#include "../model/gamemodel.h"
#include "../model/world/worldmodel.h"
#include "../model/world/worldgeneration/worldbuilder.h"

using namespace std;

class GameManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(GameModel* gameModel READ getGameModel CONSTANT)
    Q_PROPERTY(WorldModel* worldModel READ getWorldModel CONSTANT)
    Q_PROPERTY(QRect worldDimensions READ getWorldDimensions CONSTANT)

signals:

public slots:

public:
    explicit GameManager(QObject *parent = nullptr);
    Q_INVOKABLE void prepareNewGame(int width, int height, int sourcesCount);
    Q_INVOKABLE void instantiateWorld();

    GameModel* getGameModel() const;
    WorldModel* getWorldModel() const;
    QRect getWorldDimensions() const;

private:
    unique_ptr<GameModel> gameModelPtr;
    unique_ptr<WorldBuilder> worldBuilder;
    bool shouldCreateNewWorld = false;
};

#endif
