#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <QObject>
#include <memory>

#include <boost/signals2.hpp>

#include "../../model/managers/entitychangemanager.h"
#include "../../model/managers/graphentitymanager.h"
#include "../../model/managers/worldmanager.h"
#include "../models/charactersmodel.h"

namespace how {
namespace ui {
class CharactersController : public QObject {
  Q_OBJECT

public:
  CharactersController();
  CharactersController(model::EntityChangeManager *entityChangeManagerPtr,
                       model::WorldManager *WorldManagerPtr,
                       model::GraphEntityManager *graphEntityManagerPtr,
                       CharactersModel *charactersModelPtr);

public:
  Q_INVOKABLE void addMoveOrder(int characterIndex, int voronoiCellIndex);

public slots:
  void iterateAllChanges(float deltaTime);

private:
  model::EntityChangeManager *entityChangeManagerPtr;
  model::WorldManager *worldManagerPtr;
  model::GraphEntityManager *graphEntityManagerPtr;
  CharactersModel *charactersModelPtr;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
