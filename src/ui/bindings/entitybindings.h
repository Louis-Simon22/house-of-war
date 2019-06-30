#ifndef ENTITYBINDINGS_H
#define ENTITYBINDINGS_H

#include <QObject>

#include "../../model/entities/interactiveentity.h"

namespace how {
namespace ui {
class EntityBindings : public QObject {
  Q_OBJECT

  Q_PROPERTY(bool visible READ isVisible NOTIFY updateBindings FINAL)

public:
  EntityBindings();
  virtual ~EntityBindings() = 0;

signals:
  void updateBindings();

protected:
  void bindEntity(model::InteractiveEntity *interactiveEntity);

private:
  bool isVisible() const;

private:
  model::InteractiveEntity *interactiveEntity;
  boost::signals2::connection entityChangedConnection;
};
} // namespace ui
} // namespace how

#endif // ENTITYBINDINGS_H
