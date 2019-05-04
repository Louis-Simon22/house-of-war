#ifndef ENTITYMOVEMENT_H
#define ENTITYMOVEMENT_H

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>

namespace how {
namespace model {
namespace {
using change_signal_t =
    ::boost::signals2::signal<void(::boost::uuids::uuid uuid)>;
}
class EntityChange {
public:
  EntityChange();
  virtual ~EntityChange();

public:
  virtual bool progress(float deltaTime) = 0;
  virtual void destinationReached() = 0;

public:
  change_signal_t changeSignal;
};
} // namespace model
} // namespace how

#endif // ENTITYMOVEMENT_H
