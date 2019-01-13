#include "edgesmodel.h"
#include <iostream>

namespace how {
namespace bind {
namespace models {

EdgesModel::EdgesModel() : vd(nullptr) {}
EdgesModel::EdgesModel(const std::vector<point_t> *points, const vd_t *vd)
    : QAbstractListModel(), points(points), vd(vd) {}

QHash<int, QByteArray> EdgesModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[PosX] = "posX";
  roles[PosY] = "posY";
  roles[Edges] = "edges";
  return roles;
}

Qt::ItemFlags EdgesModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable;
}

QVariant EdgesModel::headerData(int, Qt::Orientation, int) const {
  return QVariant();
}

int EdgesModel::rowCount(const QModelIndex &) const {
  return this->vd->num_cells();
}

QVariant EdgesModel::data(const QModelIndex &index, int role) const {
  const auto &cell = this->vd->cells()[index.row()];
  if (cell.contains_point()) {
    switch (role) {
    default:
      return -50;
    case PosX:
      return bg::get<0>(this->points->at(index.row()));
    case PosY:
      return bg::get<1>(this->points->at(index.row()));
    case Edges:
      if (cell.incident_edge()->is_primary() &&
          cell.incident_edge()->is_finite() &&
          cell.incident_edge()->vertex0() && cell.incident_edge()->twin() &&
          cell.incident_edge()->twin()->vertex0()) {
        auto edges = std::vector<::boost::polygon::voronoi_cell<
            ::how::model::types::coordinate_fpt_t>::voronoi_edge_type>();
        edges.push_back(*cell.incident_edge());
        auto segments = QList<QVariant>();
        for (auto edge : edges) {
          auto coordinates = QList<QVariant>();
          coordinates.append(edge.vertex0()->x());
          coordinates.append(edge.vertex0()->y());
          coordinates.append(edge.vertex1()->x());
          coordinates.append(edge.vertex1()->y());
          segments.append(coordinates);
        }
        return segments;
      } else {
        auto segments = QVariantList();
        auto coordinates = QVariantList();
        coordinates.append(-5);
        coordinates.append(-5);
        coordinates.append(-10);
        coordinates.append(-10);
        segments.append(coordinates);
        coordinates = QVariantList();
        coordinates.append(5);
        coordinates.append(5);
        coordinates.append(10);
        coordinates.append(10);
        segments.append(coordinates);
        return segments;
      }
    }
  } else {
    return -10;
  }
}
} // namespace models
} // namespace bind
} // namespace how
