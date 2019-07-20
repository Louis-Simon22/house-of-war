#ifndef ARMYBINDINGS_H
#define ARMYBINDINGS_H

#include <QObject>

#include "../../model/entities/characters/army.h"
#include "./entitybindings.h"

namespace how {
namespace ui {
class ArmyBindings : public EntityBindings {
  Q_OBJECT

  Q_PROPERTY(float size READ getSize NOTIFY updateBindings)

public:
  ArmyBindings();
  ~ArmyBindings() override;

public:
  void bindArmy(model::Army *army);

private:
  types::carac_t getSize() const;

private:
  model::Army *army;
};
} // namespace ui
} // namespace how

#endif // ARMYBINDINGS_H
