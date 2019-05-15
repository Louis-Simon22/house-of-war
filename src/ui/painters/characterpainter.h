#ifndef CHARACTERPAINTER_H
#define CHARACTERPAINTER_H

#include "../../model/entities/character.h"
#include "./entitypainter.h"

namespace how {
namespace ui {
class CharacterPainter : public EntityPainter {
public:
  CharacterPainter(model::Character &character);
  ~CharacterPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  model::Character &character;
};
} // namespace ui
} // namespace how

#endif // CHARACTERPAINTER_H
