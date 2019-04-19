#ifndef POLYGONINDEXOPERATIONS_H
#define POLYGONINDEXOPERATIONS_H

#include "../graphtypes.h"

namespace how {
namespace model {

types::graph_vertex_desc_t
cellDescAtPosition(const types::polygon_index_tree_t *polygonIndexTree,
                   types::point_t position);

} // namespace model
} // namespace how

#endif // POLYGONINDEXOPERATIONS_H
