#ifndef CHARACTERPAINTER_H
#define CHARACTERPAINTER_H

#include "../../model/entities/character.h"
#include "./entitypainter.h"

namespace how {
namespace ui {
class CharacterPainter : public EntityPainter {
public:
  CharacterPainter(const model::Character &character);
  ~CharacterPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  const model::Character &character;
};
} // namespace ui
} // namespace how

#endif // CHARACTERPAINTER_H
