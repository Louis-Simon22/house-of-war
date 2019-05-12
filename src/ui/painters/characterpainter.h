#ifndef CHARACTERPAINTER_H
#define CHARACTERPAINTER_H

#include "../wrappers/characterwrapper.h"
#include "./entitypainter.h"

namespace how {
namespace ui {
class CharacterPainter : public EntityPainter {
public:
  CharacterPainter(const CharacterWrapper &characterWrapper);
  ~CharacterPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  const CharacterWrapper &characterWrapper;
};
} // namespace ui
} // namespace how

#endif // CHARACTERPAINTER_H
