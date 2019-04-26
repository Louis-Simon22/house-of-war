#ifndef NOTIFIABLEABSTRACTLISTMODEL_H
#define NOTIFIABLEABSTRACTLISTMODEL_H

#include <QAbstractListModel>

#include <boost/uuid/uuid.hpp>

namespace how {
namespace ui {
namespace {
namespace uuids = ::boost::uuids;
}
class EntityModel : public QAbstractListModel {
public:
  EntityModel();
  virtual ~EntityModel();

public:
  void entityChanged(const uuids::uuid& uuid);

protected:
  std::map<const uuids::uuid, QModelIndex> uuidToIndexMap;
};
} // namespace ui
} // namespace how
#endif // NOTIFIABLEABSTRACTLISTMODEL_H
