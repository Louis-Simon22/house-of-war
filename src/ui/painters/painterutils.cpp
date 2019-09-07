#include "painterutils.h"

namespace how {
namespace ui {

std::vector<types::point_t> getCornersOfRectangle(float x, float y, float width,
                                                  float height) {
  auto halfwidth = width / 2;
  auto halfheight = height / 2;
  return {types::point_t(x - halfwidth, y - halfheight),
          types::point_t(x + halfwidth, y - halfheight),
          types::point_t(x + halfwidth, y + halfheight),
          types::point_t(x - halfwidth, y + halfheight)};
}

} // namespace ui
} // namespace how
