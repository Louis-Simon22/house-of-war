#ifndef ARMYWRAPPER_H
#define ARMYWRAPPER_H

#include "../../model/entities/army.h"
#include "./selectableentitywrapper.h"

namespace how {
namespace ui {
class ArmyWrapper : public SelectableEntityWrapper {
public:
  ArmyWrapper(model::Army &army);
  ~ArmyWrapper() override;

public:
  EntityPainter *createEntityPainter() const override;
  types::coordinate_t getPosX() const override;
  types::coordinate_t getPosY() const override;
  types::coordinate_t getWidth() const override;
  types::coordinate_t getHeight() const override;
  int getLayer() const override;
  bool isTargetable() const override;

private:
  model::Army &army;
};
} // namespace ui
} // namespace how

#endif // ARMYWRAPPER_H
