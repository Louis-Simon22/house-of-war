#ifndef CHARACTERWRAPPER_H
#define CHARACTERWRAPPER_H

#include "../../model/entities/character.h"
#include "./selectableentitywrapper.h"

namespace how {
namespace ui {
class CharacterWrapper : public SelectableEntityWrapper {
public:
  CharacterWrapper(model::Character &character);

public:
  EntityPainter *createEntityPainter() const override;
  types::coordinate_t getPosX() const override;
  types::coordinate_t getPosY() const override;
  types::coordinate_t getWidth() const override;
  types::coordinate_t getHeight() const override;
  int getLayer() const override;
  bool isTargetable() const override;
  bool isSelected() const override;

private:
  model::Character &character;
};
} // namespace ui
} // namespace how

#endif // CHARACTERWRAPPER_H
