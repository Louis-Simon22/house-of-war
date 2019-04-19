#ifndef CHARACTERSCONTROLLER_H
#define CHARACTERSCONTROLLER_H

#include <QObject>
#include <memory>

#include <boost/signals2.hpp>

#include "../../model/entities/characters/characterdata.h"
#include "../../model/entities/entitychangemanager.h"
#include "../../model/world/worlddata.h"
#include "../models/charactersmodel.h"

namespace how {
namespace ui {
class CharactersController : public QObject {
  Q_OBJECT

public:
  CharactersController();
  CharactersController(model::EntityChangeManager *entityChangeManagerPtr,
                       model::WorldData *worldDataPtr,
                       model::CharacterData *characterDataPtr,
                       CharactersModel *charactersModelPtr);

public:
  Q_INVOKABLE void addMoveOrder(int characterIndex, int voronoiCellIndex);

public slots:
  void iterateAllChanges(float deltaTime);

private:
  model::EntityChangeManager *entityChangeManagerPtr;
  model::WorldData *worldDataPtr;
  model::CharacterData *characterDataPtr;
  CharactersModel *charactersModelPtr;
};
} // namespace ui
} // namespace how

#endif // CHARACTERSCONTROLLER_H
