#include "influencezone.h"

namespace how {
namespace model {

InfluenceZone::InfluenceZone(const GraphEntity &attachedEntity)
    : attachedEntity(attachedEntity) ,changedSignal(){}

InfluenceZone::~InfluenceZone() {}

} // namespace model
} // namespace how
