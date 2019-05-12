#ifndef ENTITYWRAPPER_H
#define ENTITYWRAPPER_H

#include <QObject>

#include "../../model/graphtypes.h"
#include "../painters/entitypainter.h"

namespace how {
namespace ui {
namespace {
namespace uuids = ::boost::uuids;
}
class EntityWrapper : public QObject {
  Q_OBJECT

public:
  EntityWrapper();
  virtual ~EntityWrapper();

public:
  bool isSelected() const;
  void setSelected(bool selected);

signals:
  void updateEntityPainter();

public:
  virtual EntityPainter *createEntityPainter() const = 0;
  virtual types::coordinate_t getPosX() const = 0;
  virtual types::coordinate_t getPosY() const = 0;
  virtual types::coordinate_t getWidth() const = 0;
  virtual types::coordinate_t getHeight() const = 0;
  virtual int getLayer() const = 0;
  virtual types::graph_vertex_desc_t getVertexDesc() const = 0;
  virtual bool isTargetable() const = 0;
  virtual bool isSelectable() const = 0;

public:
  virtual void onEntityWrapperTargeted(EntityWrapper *target) = 0;

private:
  bool selected;
};
} // namespace ui
} // namespace how

#endif // ENTITYWRAPPER_H
