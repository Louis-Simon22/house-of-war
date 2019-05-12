#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace uuids = ::boost::uuids;
using dimensions_changed_signal_t = ::boost::signals2::signal<void()>;
using visual_changed_signal_t = ::boost::signals2::signal<void()>;
using destruction_signal_t = ::boost::signals2::signal<void()>;
} // namespace
class GraphEntity {
public:
  static constexpr types::layer_t DEFAULT_LAYER = 0;

public:
  GraphEntity();
  GraphEntity(types::layer_t layer);
  virtual ~GraphEntity();

public:
  virtual types::coordinate_t getPosX() const = 0;
  virtual types::coordinate_t getPosY() const = 0;
  virtual types::coordinate_t getWidth() const = 0;
  virtual types::coordinate_t getHeight() const = 0;
  virtual bool isTargetable() const = 0;
  virtual bool isSelectable() const = 0;

public:
  const uuids::uuid &getUuid() const;
  types::point_t getPosition() const;
  types::layer_t getLayer() const;
  bool isSelected() const;
  void setSelected(bool selected);

private:
  uuids::uuid uuid;
  types::layer_t layer;
  bool selected;

public:
  dimensions_changed_signal_t dimensionsChangedSignal;
  visual_changed_signal_t visualChangedSignal;
  destruction_signal_t destructionSignal;
};
} // namespace model
} // namespace how

#endif // GRAPHENTITY_H
