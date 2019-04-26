#include "converter.h"

namespace how {
namespace ui {

QPointF convertF(const types::point_t &point) {
  return QPointF(static_cast<double>(bg::get<0>(point)),
                 static_cast<double>(bg::get<1>(point)));
}

QRect convert(const types::box_t &box) {
  const auto posX = bg::get<bg::min_corner, 0>(box);
  const auto posY = bg::get<bg::min_corner, 1>(box);
  const auto width =
      bg::get<bg::max_corner, 0>(box) - bg::get<bg::min_corner, 0>(box);
  const auto height =
      bg::get<bg::max_corner, 1>(box) - bg::get<bg::min_corner, 1>(box);
  return QRect(static_cast<int>(posX), static_cast<int>(posY),
               static_cast<int>(width), static_cast<int>(height));
}

} // namespace ui
} // namespace how
