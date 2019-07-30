#ifndef TILEBINDINGS_H
#define TILEBINDINGS_H

#include <QObject>

#include "../../model/entities/terrain/tile.h"
#include "./entitybindings.h"

namespace how {
namespace ui {
class TileBindings : public EntityBindings {
  Q_OBJECT

  Q_PROPERTY(float resources READ getResources NOTIFY updateBindings)

public:
  TileBindings();
  ~TileBindings() override;

public:
  void bindTile(model::Tile *tile);

private:
  types::carac_t getResources() const;

private:
  model::Tile *tile;
};
} // namespace ui
} // namespace how

#endif // TILEBINDINGS_H
