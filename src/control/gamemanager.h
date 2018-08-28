#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <memory>
#include "../model/gamemodel.h"
#include "../model/geography/worldmodel.h"

using namespace std;

class GameManager : public QObject {
    Q_OBJECT
private:
    unique_ptr<GameModel> gameModel;

public:
    explicit GameManager(QObject *parent = nullptr);
    Q_INVOKABLE WorldModel* getWorldModel();

signals:

public slots:
    void startNewGame(int width, int height, int sourcesCount);
};

#endif
