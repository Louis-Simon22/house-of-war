#ifndef GRAPHENTITYMANAGERQMLWRAPPER_H
#define GRAPHENTITYMANAGERQMLWRAPPER_H

#include <QObject>
#include <memory>

#include "../../model/managers/graphentitymanager.h"
#include "../models/armiesmodel.h"
#include "../models/charactersmodel.h"

namespace how {
namespace ui {
class GraphEntityManagerQMLWrapper : public QObject {
  Q_OBJECT

  Q_PROPERTY(CharactersModel *charactersModel READ getCharactersModel CONSTANT)
  Q_PROPERTY(ArmiesModel *armiesModel READ getArmiesModel CONSTANT)

public:
  GraphEntityManagerQMLWrapper();
  GraphEntityManagerQMLWrapper(model::GraphEntityManager *graphEntityManager);

public:
  CharactersModel *getCharactersModel() const;
  ArmiesModel *getArmiesModel() const;

private:
  const model::GraphEntityManager *graphEntityManagerPtr;
  std::unique_ptr<CharactersModel> charactersModelPtr;
  std::unique_ptr<ArmiesModel> armiesModelPtr;
};
} // namespace ui
} // namespace how

#endif // GRAPHENTITYMANAGERQMLWRAPPER_H
