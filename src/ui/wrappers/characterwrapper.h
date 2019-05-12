#ifndef CHARACTERWRAPPER_H
#define CHARACTERWRAPPER_H

#include "../../model/entities/character.h"
#include "./entitywrapper.h"

namespace how {
namespace ui {

class CharacterController;

class CharacterWrapper : public EntityWrapper {
public:
  CharacterWrapper(CharacterController &characterController,
                   model::Character &character);
  ~CharacterWrapper() override;

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

public:
  void onEntityWrapperTargeted(EntityWrapper *target) override;

public:
  model::Character &getCharacter();
  const model::Character &getCharacter() const;

private:
  CharacterController &characterController;
  model::Character &character;
};
} // namespace ui
} // namespace how

#include "../control/charactercontroller.h"

#endif // CHARACTERWRAPPER_H
