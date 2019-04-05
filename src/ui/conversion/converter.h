#ifndef CONVERTER_H
#define CONVERTER_H

#include <QPolygon>
#include <QRect>
#include <QVariantList>
#include <vector>

#include "../../model/modeltypes.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}
QVariantList
convert(const std::vector<model::types::segment_t> *outlineSegments);

QVariantList convert(const std::vector<model::types::point_t> *points);

QPoint convert(const model::types::point_t point);

QRect convert(const model::types::box_t *box);

QPolygon convert(const model::types::polygon_t *polygon);

} // namespace ui
} // namespace how

#endif // CONVERTER_H
