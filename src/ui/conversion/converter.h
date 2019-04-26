#ifndef CONVERTER_H
#define CONVERTER_H

#include <QPointF>
#include <QRect>

#include "../../model/modeltypes.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

QPointF convertF(const types::point_t &point);

QRect convert(const types::box_t &box);

} // namespace ui
} // namespace how

#endif // CONVERTER_H
