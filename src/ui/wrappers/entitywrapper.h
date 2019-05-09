#ifndef ENTITYWRAPPER_H
#define ENTITYWRAPPER_H

#include <QObject>

#include "../../model/entities/entity.h"
#include "../../model/modeltypes.h"
#include "../painters/entitypainter.h"

namespace how {
namespace ui {
class EntityWrapper : QObject {
public:
  EntityWrapper();
  virtual ~EntityWrapper();

signals:
  void updateEntityPainter();

public:
  virtual EntityPainter *createEntityPainter() const = 0;
  virtual types::coordinate_t getPosX() const = 0;
  virtual types::coordinate_t getPosY() const = 0;
  virtual types::coordinate_t getWidth() const = 0;
  virtual types::coordinate_t getHeight() const = 0;
  virtual int getLayer() const = 0;
  virtual bool isTargetable() const = 0;
  virtual bool isSelectable() const = 0;
};
} // namespace ui
} // namespace how

#endif // ENTITYWRAPPER_H
