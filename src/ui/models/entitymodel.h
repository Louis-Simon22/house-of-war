#ifndef NOTIFIABLEABSTRACTLISTMODEL_H
#define NOTIFIABLEABSTRACTLISTMODEL_H

#include <QAbstractListModel>

#include <boost/uuid/uuid.hpp>

namespace how {
namespace ui {
class EntityModel : public QAbstractListModel {
public:
  EntityModel();
  ~EntityModel();

public:
  void entityChanged(::boost::uuids::uuid uuid);

protected:
  std::map<const ::boost::uuids::uuid, QModelIndex> uuidToIndexMap;
};
} // namespace ui
} // namespace how
#endif // NOTIFIABLEABSTRACTLISTMODEL_H
