#ifndef CELLDATA_H
#define CELLDATA_H

#include "../modeltypes.h"

namespace how {
namespace model {

struct CellData {
public:
  CellData();

public:
  types::characteristics_t elevation;
};
} // namespace model
} // namespace how

#endif // CELLDATA_H
