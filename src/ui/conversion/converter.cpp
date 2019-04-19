#include "converter.h"

namespace how {
namespace ui {

QPointF convertF(const types::point_t& point) {
  return QPointF(bg::get<0>(point), bg::get<1>(point));
}

QRect convert(const types::box_t& box) {
  return QRect(
      bg::get<bg::min_corner, 0>(box), bg::get<bg::min_corner, 1>(box),
      bg::get<bg::max_corner, 0>(box) - bg::get<bg::min_corner, 0>(box),
      bg::get<bg::max_corner, 1>(box) - bg::get<bg::min_corner, 1>(box));
}

} // namespace ui
} // namespace how
