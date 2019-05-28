#ifndef ENTITYMOVEMENT_H
#define ENTITYMOVEMENT_H

namespace how {
namespace model {
class GraphEntityChange {
public:
  GraphEntityChange();
  virtual ~GraphEntityChange();

public:
  virtual bool progress() = 0;
  virtual void destinationReached() = 0;
};
} // namespace model
} // namespace how

#endif // ENTITYMOVEMENT_H
