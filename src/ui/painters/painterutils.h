#ifndef PAINTERUTILS_H
#define PAINTERUTILS_H

#include <vector>

#include "../../model/modeltypes.h"

namespace how {
namespace ui {

std::vector<types::point_t> getCornersOfRectangle(float x, float y, float width,
                                                  float height);

} // namespace ui
} // namespace how

#endif // PAINTERUTILS_H
