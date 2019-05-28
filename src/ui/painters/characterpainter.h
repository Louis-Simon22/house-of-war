#ifndef CHARACTERPAINTER_H
#define CHARACTERPAINTER_H

#include "../../model/entities/character.h"
#include "./graphentitypainter.h"

namespace how {
namespace ui {
class CharacterPainter : public PainterItem {
public:
  CharacterPainter(QQuickItem *parent,
                   std::shared_ptr<model::Character> characterPtr);
  ~CharacterPainter() override;

public:
  void updateDimensions() override;
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  std::shared_ptr<model::Character> characterPtr;
};
} // namespace ui
} // namespace how

#endif // CHARACTERPAINTER_H
