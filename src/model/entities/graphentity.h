#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace uuids = ::boost::uuids;
using physical_change_signal_t =
    ::boost::signals2::signal<void(const uuids::uuid& uuid)>;
using visual_change_signal_t =
    ::boost::signals2::signal<void()>;
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

private:
  uuids::uuid uuid;
  types::layer_t layer;

public:
  physical_change_signal_t physicalChangSignal;
  visual_change_signal_t visualChangeSignal;
};
} // namespace model
} // namespace how

#endif // GRAPHENTITY_H
