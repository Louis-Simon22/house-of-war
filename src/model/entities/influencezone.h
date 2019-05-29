#ifndef INFLUENCEZONE_H
#define INFLUENCEZONE_H

#include <boost/signals2.hpp>

#include "../modeltypes.h"
#include "./graphentity.h"

namespace how {
namespace model {
class InfluenceZone {
public:
  using changed_signal_t = ::boost::signals2::signal<void()>;

public:
  InfluenceZone(const GraphEntity &attachedEntity);
  virtual ~InfluenceZone() = 0;

public:
  virtual bool isPointWithinZone(types::coordinate_t posX,
                                 types::coordinate_t posY) const = 0;
  virtual bool isPolygonOverlappingZone(types::polygon_t polygon) const = 0;
  virtual types::box_t getEnvelope() const = 0;

protected:
  const GraphEntity &attachedEntity;

public:
  changed_signal_t changedSignal;
};
} // namespace model
} // namespace how

#endif // INFLUENCEZONE_H
