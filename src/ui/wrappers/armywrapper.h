#ifndef ARMYWRAPPER_H
#define ARMYWRAPPER_H

#include "../../model/entities/army.h"
#include "./entitywrapper.h"

namespace how {
namespace ui {

class ArmyController;

class ArmyWrapper : public EntityWrapper {
public:
  ArmyWrapper(ArmyController &armyController, model::Army &army);
  ~ArmyWrapper() override;

  // TODO put all this functionality in the model?
public:
  EntityPainter *createEntityPainter() const override;
  types::coordinate_t getPosX() const override;
  types::coordinate_t getPosY() const override;
  types::coordinate_t getWidth() const override;
  types::coordinate_t getHeight() const override;
  int getLayer() const override;
  types::graph_vertex_desc_t getVertexDesc() const override;
  bool isTargetable() const override;
  bool isSelectable() const override;

// TODO what about this functionality?
public:
  void onEntityWrapperTargeted(EntityWrapper *target) override;

public:
  model::Army &getArmy();
  const model::Army &getArmy() const;

private:
  ArmyController &armyController;
  model::Army &army;
};

} // namespace ui
} // namespace how

#include "../control/armycontroller.h";

#endif // ARMYWRAPPER_H
