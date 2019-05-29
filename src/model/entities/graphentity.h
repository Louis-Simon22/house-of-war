#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H

#include <boost/signals2.hpp>

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
} // namespace
class GraphEntity {
public:
  using changed_signal_t = ::boost::signals2::signal<void()>;

public:
  GraphEntity(types::layer_t layer, types::point_t position);
  virtual ~GraphEntity();

public:
  virtual bool isWithinSelectionArea(types::coordinate_t posX,
                                     types::coordinate_t posY) const = 0;
  virtual bool isTargetable() const = 0;
  virtual bool isSelectable() const = 0;

public:
  types::layer_t getLayer() const;
  types::coordinate_t getPosX() const;
  types::coordinate_t getPosY() const;
  const types::point_t &getPosition() const;
  void setPosition(const types::point_t &position);
  bool isSelected() const;
  void setSelected(bool selected);

private:
  types::layer_t layer;
  types::point_t position;
  bool selected;

public:
  changed_signal_t changedSignal;
};

} // namespace model
} // namespace how

#endif // GRAPHENTITY_H
