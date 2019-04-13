#ifndef CONVERTER_H
#define CONVERTER_H

#include <QPointF>
#include <QRect>
#include <QVariantList>
#include <vector>

#include "../../model/modeltypes.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

QPointF convertF(const model::types::point_t &point);

QRect convert(const model::types::box_t &box);

} // namespace ui
} // namespace how

#endif // CONVERTER_H
