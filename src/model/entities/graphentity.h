#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
namespace uuids = ::boost::uuids;
} // namespace
class GraphEntity {
public:
  using dimensions_changed_signal_t = ::boost::signals2::signal<void()>;
  using visual_changed_signal_t = ::boost::signals2::signal<void()>;
  using destruction_signal_t = ::boost::signals2::signal<void()>;

public:
  GraphEntity(types::layer_t layer, types::point_t position);
  virtual ~GraphEntity();

public:
  virtual bool isWithinSelectionArea(types::coordinate_t posX,
                                     types::coordinate_t posY) const = 0;
  virtual bool isTargetable() const = 0;
  virtual bool isSelectable() const = 0;

public:
  const uuids::uuid &getUuid() const;
  types::layer_t getLayer() const;
  types::coordinate_t getPosX() const;
  types::coordinate_t getPosY() const;
  const types::point_t &getPosition() const;
  void setPosition(const types::point_t &position);
  bool isSelected() const;
  void setSelected(bool selected);

private:
  uuids::uuid uuid;
  types::layer_t layer;
  types::point_t position;
  bool selected;

public:
  dimensions_changed_signal_t dimensionsChangedSignal;
  visual_changed_signal_t visualChangedSignal;
};

} // namespace model
} // namespace how

#endif // GRAPHENTITY_H
