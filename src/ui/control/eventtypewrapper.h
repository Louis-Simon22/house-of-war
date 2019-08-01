#ifndef CONTROLMODEWRAPPER_H
#define CONTROLMODEWRAPPER_H

#include <QObject>

#include "../../model/managers/eventtype.h"

namespace how {
namespace ui {
class EventTypeWrapper : public QObject {
  Q_GADGET

public:
  EventTypeWrapper();
  ~EventTypeWrapper();

public:
  Q_ENUM(model::EventType)
};
} // namespace ui
} // namespace how

#endif // CONTROLMODEWRAPPER_H
