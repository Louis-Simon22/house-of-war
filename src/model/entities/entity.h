#ifndef ENTITY_H
#define ENTITY_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace how {
namespace model {
namespace {
namespace uuids = ::boost::uuids;
}
struct Entity {
public:
  Entity();
  ~Entity();

public:
  uuids::uuid uuid;
};
} // namespace model
} // namespace how

#endif // ENTITY_H
